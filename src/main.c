/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:40:01 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/07 16:05:22 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "env.h"
#include <unistd.h>

int	g_exit_status = 0;

static void	print_token_list(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	printf("\nToken List:\n");
	while (current)
	{
		printf("Type: %d, Content: '%s'\n", current->type, current->content);
		current = current->next;
	}
	printf("\n");
}

static void	print_ast_node(t_ast_node *node, int depth)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	while (i++ < depth)
		printf("  ");
	printf("Node Type: %d\n", node->type);
	if (node->args)
	{
		i = 0;
		while (node->args[i])
		{
			printf("  Arg[%d]: %s\n", i, node->args[i]);
			i++;
		}
	}
	if (node->left || node->right)
	{
		printf("  Left:\n");
		print_ast_node(node->left, depth + 1);
		printf("  Right:\n");
		print_ast_node(node->right, depth + 1);
	}
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_token		*tokens;
	t_ast_node	*ast;
	t_env		**env_;

	(void)argc;
	(void)argv;
	env_ = get_env_list();
	*env_ = build_env(env);
	print_banner();
	while (true)
	{
		line = readline("minishell👾 > ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			tokens = tokenize(line);
			if (tokens)
			{
				printf("\033[0;34m");
				print_token_list(tokens);
				ast = parse(tokens);
				if (ast)
				{
					printf("\033[0;32m");
					printf("\nAST Structure:\n");
					print_ast_node(ast, 0);
					printf("\033[0m");
					executor(ast);
					free_ast(ast);
				}
				free_tokens(tokens);
			}
		}
		free(line);
	}
	printf("\nGoodbye!\n");
	return (EXIT_SUCCESS);
}

