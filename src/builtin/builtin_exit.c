/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 23:06:50 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/23 10:47:31 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <limits.h>

static bool is_valid_numeric(char *arg)
{
	int i;
	int j;

	i = 0;
	while (arg[i] && (arg[i] == ' ' || arg[i] == '\t'))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	j = 0;
	while (arg[i + j] && isdigit(arg[i + j]))
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
	while (arg[i] && isdigit(arg[i]))
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
int	builtin_exit(t_exec *cmd)
{
	ft_putendl_fd("exit", STDIN_FILENO);
	if (cmd && cmd->argc == 1)
	{
		// Free memory 
		exit((int)((unsigned char)get_exit_status()));
	}
	if (!is_valid_numeric(cmd->argv[1]) || !is_within_long_range(cmd->argv[1]))
	{
		ft_putendl_fd("minishell: exit: numeric argument required", STDERR_FILENO);
		// Free memory 
		exit(255);
	}
	if (cmd->argc > 2)
	{
		ft_putendl_fd("minishell: exit: Too many arguments", STDERR_FILENO);
		return (1);
	}
	exit((int)((unsigned char)ft_atoi(cmd->argv[1]))); //unsigned char to ensure within 0-255
	return (0);
}
