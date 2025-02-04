/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 17:54:05 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/04 15:45:48 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
	echo with -n do not output the trailing newline
	echo with no args, output a newline
	echo with multiple -n, skip those -n
	echo with invalid -n, e.g. -nn, do not output the trailing newline
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
	printf("Debug - echo args start:\n");  // Debug
	int j = 0; //debug
	while (node->args[j])
	{
		printf("Debug - arg[%d]: '%s'\n", j, node->args[j]);  // Debug
		j++;
	}
	while (node->args[i] && ft_strcmp(node->args[i], "-n") == 0
		&& valid_n_flag(node->args[i]))
	{
		no_newline = 1;
		i++;
	}
	while (node->args[i])
	{
		printf("Debug - processing arg: '%s'\n", node->args[i]);  // Debug
		if (ft_strcmp(node->args[i], "$?") == 0) // Expand `$?`
			printf("%d", get_exit_status());
		else if (node->args[i][0] == '$')
		{
			const char *key = &node->args[i][1];  // Skip the $
			printf("Debug - looking up key: '%s'\n", key);  // Debug
			char *value = get_env_value(*(node->env), key);
			printf("Debug - found value: '%s'\n", value ? value : "NULL");  // Debug
			if (value)
				printf("%s", value);
			else
				printf("%s", "");
		}
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
