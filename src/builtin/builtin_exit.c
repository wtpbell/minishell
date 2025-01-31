/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 23:06:50 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/31 14:14:25 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

static bool	is_valid_numeric(char *arg)
{
	int	i;
	int	j;

	i = 0;
	while (arg[i] && (arg[i] == ' ' || arg[i] == '\t'))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	j = 0;
	while (arg[i + j] && ft_isdigit(arg[i + j]))
		j++;
	if (j > MAX_STATUS_LEN)
		return (false);
	i += j;
	while (arg[i] && (arg[i] == ' ' || arg[i] == '\t'))
		i++;
	if (arg[i] != '\0')
		return (false);
	return (true);
}

static bool	is_within_long_range(char *arg)
{
	long long	num;
	int			sign;
	int			i;

	num = 0;
	sign = 1;
	i = 0;
	while (arg[i] && (arg[i] == ' ' || arg[i] == '\t'))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (arg[i] == '-')
			sign = -1;
		i++;
	}
	while (arg[i] && ft_isdigit(arg[i]))
	{
		if ((num > LLONG_MAX / 10) ||
			(num == LLONG_MAX / 10 && (arg[i] - '0') > LLONG_MAX % 10))
			return (false);
		num = num * 10 + (arg[i] - '0');
		i++;
	}
	num *= sign;
	return (num <= LLONG_MAX && num >= LLONG_MIN);
}
/*
	No Arguments: Exits with status 0 (default).
	Single Numeric Argument: Exits with the given status.
	Single Non-Numeric Argument: Displays an error and exits with status 2.
	Multiple Arguments: Displays an error and does not exit.
*/
int	builtin_exit(t_ast_node *node)
{
	char	**args;

	args = node->args;
	ft_putendl_fd("exit", STDIN_FILENO);
	if (node->argc == 1)
	{
		// Free memory
		exit((int)((unsigned char)get_exit_status()));
	}
	if (!(is_valid_numeric(args[1]) && is_within_long_range(args[1])))
	{
		ft_putendl_fd("minishell: exit: numeric argument required", STDERR_FILENO);
		// Free memory
		exit(255);
	}
	if (node->argc > 2)
	{
		ft_putendl_fd("minishell: exit: Too many arguments", STDERR_FILENO);
		return (1);
	}
	exit((int)((unsigned char)ft_atoi(node->args[1])));
	return (0);
}
