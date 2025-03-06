/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:40:01 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/06 16:34:11 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "env.h"
#include "common.h"
#include <unistd.h>

static int	process_command_line(char *line, t_env **env_)
{
	t_token		*tokens;
	t_ast_node	*ast;

	if (!validate_quotes(line))
	{
		set_exit_status(2);
		return (0);
	}
	tokens = tokenize(line);
	if (!tokens)
		return (0);
	ast = parse(tokens);
	if (ast)
	{
		executor(ast, env_);
		free_ast(ast);
	}
	free_tokens(tokens);
	return (1);
}

static void	main_loop(t_env **env_)
{
	char	*line;
	char	*prompt;

	while (1)
	{
		prompt = get_custom_prompt();
		line = readline(prompt);
		free(prompt);
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			process_command_line(line, env_);
		}
		free(line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_env	**env_;

	(void)argc;
	(void)argv;
	env_ = get_env_list();
	*env_ = build_env(env);
	signals_init();
	print_banner();
	main_loop(env_);
	free_env(env_);
	return (EXIT_SUCCESS);
}
