/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:40:01 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/30 09:47:15 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "parser.h"

int	g_exit_status = 0;

int	main(void)
{
	char		*line;
	t_token		*tokens;
	t_ast_node	*ast;

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
		// TODO: Execute AST
		free_ast(ast);
		free(line);
	}
	return (EXIT_SUCCESS);
}


