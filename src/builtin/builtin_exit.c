/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 23:06:50 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/22 21:30:45 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"


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

/*
	No Arguments: Exits with status 0 (default).
	Single Numeric Argument: Exits with the given status.
	Single Non-Numeric Argument: Displays an error and exits with status 2.
	Multiple Arguments: Displays an error and does not exit.
*/
int	builtin_exit(t_exec *cmd)
{
	ft_putendl_fd("exit", STDIN_FILENO);
	if (cmd->argc == 1)
	{
		//need to free memory
		exit((int)((unsigned char)get_exit_status()));
	}
	if (!is_valid_numeric(cmd->argv[1]))
	{
		ft_putendl_fd("minishell: exit: numeric argument required",
			STDERR_FILENO);
		//need to free memory
		exit(255);
	}
	if (cmd->argc > 2)
	{
		ft_putendl_fd("minishell: exit: Too many arguments", STDERR_FILENO);
		return (1);
	}
	exit((int)((unsigned char)ft_atoi(cmd->argv[1])));
	return (0);
}
