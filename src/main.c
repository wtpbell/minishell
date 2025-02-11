/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:40:01 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/11 15:04:59 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"

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

static void    print_ast_node(t_ast_node *node, int depth)
{
	int				i;
	t_redirection	*redir;

	if (!node)
		return ;
	printf("%*sNode Type: %d\n", depth * 2, "", node->type);
	if (node->args)
    {
		printf("%*sArgs: ", depth * 2, "");
		i = 0;
		while (node->args[i])
		{
			printf("'%s' ", node->args[i]);
			i++;
		}
		printf("\n");
	}
	if (node->redirections)
	{
		printf("%*sRedirections: ", depth * 2, "");
		redir = node->redirections;
		while (redir)
		{
			printf("type=%d file='%s' -> ", redir->type, redir->file);
			redir = redir->next;
		}
		printf("\n");
	}
	if (node->left)
	{
		printf("%*sLeft child:\n", depth * 2, "");
		print_ast_node(node->left, depth + 1);
	}
	if (node->right)
	{
		printf("%*sRight child:\n", depth * 2, "");
		print_ast_node(node->right, depth + 1);
	}
}

int	main(void)
{
	char		*line;
	t_token		*tokens;
	t_ast_node	*ast;

	print_banner();
	while (1)
	{
		line = readline("minishell-parser👾 > ");
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
