/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:40:01 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/29 17:43:10 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "executor.h"
#include "env.h"


#include <unistd.h>
#include <asm-generic/termbits.h>

/*
	Disable canonical (line-buffered) mode with ICANON
	Disable ECHOCTL, 
*/
void	init_terminal(void)
{
	struct termios	orig_term;
	struct termios	new_term;

	if (!isatty(STDIN_FILENO))
		return ;
	tcgetattr(STDIN_FILENO, &orig_term);
	new_term = orig_term;
	new_term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}

static void	minishell(void)
{
	char		*line;
	t_token		*tokens;
	t_ast_node	*ast;

	while (true)
	{
		line = readline("minishell> ");
		if (!line)
			break;
		if (*line)
			add_history(line);
		tokens = tokenize(line);
		ast = parse(tokens);
		if (ast)
			executor(ast);
		free_ast(ast);
		free(line);
		free_tokens(tokens);
	}
}
int	main(int ac, char **av, char **env)
{
	t_env	**env_;

	(void)ac;
	(void)av;
	g_exit_status = 0;
	env_ = get_env_list();
	*env_ = build_env(env);
	init_terminal();
	minishell();
	init_terminal();
	free_env(env_);
	return (EXIT_SUCCESS);
}

