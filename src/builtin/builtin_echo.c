/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 17:54:05 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/13 17:32:59 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	verify_args(char **args)
{
	int	i;
	int	j;

	if (ft_strcmp(args[1], "-") == 0)
		return (1);
	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		j = 0;
		while (args[i][++j])
		{
			if (args[i][j] != 'n')
				return (i);
		}
		i++;
	}
	return (i);
}

int	builtin_echo(t_ast_node *node, t_env **env, t_token *tokens)
{
	int	i;
	int	print_newline;

	(void)env;
	(void)tokens;
	if (node->argc == 1)
		return (printf("\n"), EXIT_SUCCESS);
	i = verify_args(node->args);
	print_newline = (i == 1);
	while (i < node->argc)
	{
		printf("%s", node->args[i]);
		if (i + 1 < node->argc)
			printf(" ");
		i++;
	}
	if (print_newline)
		printf("\n");
	return (EXIT_SUCCESS);
}
