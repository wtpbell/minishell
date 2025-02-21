/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 17:54:05 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/21 08:40:29 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
	echo with -n do not output the trailing newline
	echo with no args, output a newline
	echo with multiple -n, skip those -n
	echo with invalid -n, e.g. -nn, do not output the trailing newline
*/
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

static int	is_escaped_var(const char *str)
{
	return (str[0] == '\\' && str[1] == '$' && str[2] == '?');
}

int	builtin_echo(t_ast_node *node, t_env **env)
{
	int	i;

	(void)env;
	if (node->argc == 1)
		return (printf("\n"), EXIT_SUCCESS);
	i = verify_args(node->args);
	while (i < node->argc)
	{
		if (is_escaped_var(node->args[i]))
			printf("%s", node->args[i]);
		else if (node->args[i][0] == '\\')
			printf("%s", node->args[i] + 1);
		else
			printf("%s", node->args[i]);
		i++;
		if (i < node->argc)
			printf(" ");
	}
	if (verify_args(node->args) == 1)
		printf("\n");
	return (EXIT_SUCCESS);
}
