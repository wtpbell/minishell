/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:40:01 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/22 21:56:43 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "env.h"

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_token		*tokens;
	t_ast_node	*ast;
	t_env		**env_;

	(void)ac;
	(void)av;
	g_exit_status = 0;
	while (true)
	{
		env_ = get_env_list();
		*env_ = create_list(env);
		line = readline("minishell> ");
		if (!line)
			break ; //this may need to free memory
		if (*line)
			add_history(line);
		tokens = tokenize(line);
		ast = parse(tokens);
		if (ast)
			executor(&ast);
		free_ast(ast);
		free(line);
	}
	return (EXIT_SUCCESS);
}
