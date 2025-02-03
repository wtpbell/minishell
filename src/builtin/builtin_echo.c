/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 17:54:05 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/03 15:47:53 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
	echo with -n do not output the trailing newline
	echo with no args, output a newline
	echo with multiple -n, skip those -n
	echo with invalid -n, e.g. -nn, will directly output -nn
*/
static int	valid_n_flag(const char *arg)
{
	int	i;

	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(t_ast_node *node)
{
	int	i;
	int	no_newline;

	i = 1;
	no_newline = 0;
	if (!node || !node->args)
		return (set_exit_status(1), EXIT_FAILURE);
	while (node->args[i] && ft_strcmp(node->args[i], "-n") == 0
		&& valid_n_flag(node->args[i]))
	{
		no_newline = 1;
		i++;
	}
	while (node->args[i])
	{
		if (ft_strcmp(node->args[i], "$?") == 0) // Expand `$?`
			printf("%d", get_exit_status());
		else
			printf("%s", node->args[i]);
		if (node->args[i + 1])
			printf(" ");
		i++;
	}
	if (!no_newline)
		printf("\n");
	return (set_exit_status(0), EXIT_SUCCESS);
}
