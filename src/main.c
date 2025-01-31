/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:40:01 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/30 17:50:21 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "env.h"
#include <unistd.h>

int	g_exit_status = 0;


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
	if (!*env_)
	{
		printf("build_env() returned NULL\n");
		exit(EXIT_FAILURE);
	}

	print_banner();
	while (true)
	{
		line = readline("minishell👾 > ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		tokens = tokenize(line);
		ast = parse(tokens);
		if (ast)
			executor(ast);
		free_ast(ast);
		free(line);
	}
	return (EXIT_SUCCESS);
}

