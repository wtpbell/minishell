/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 23:06:50 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/21 23:19:15 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static bool is_valid_numeric(char *arg)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (arg[i] && (arg[i] == ' ' || arg[i] == '\t'))
		i++;

	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i + j] && isdigit(arg[i + j]))
		j++;
	if (j > MAX_STATUS_LEN)
		return false;
	i += j;
	while (arg[i] && (arg[i] == ' ' || arg[i] == '\t'))
		i++;
	return (arg[i] == '\0');
}

/*
	No Arguments: Exits with status 0 (default).
	Single Numeric Argument: Exits with the given status.
	Single Non-Numeric Argument: Displays an error and exits with status 2.
	Multiple Arguments: Displays an error and does not exit.
*/
int	builtin_exit(t_exec *cmd)
{
	int	exit_code;

	printf("exit\n");
	if (cmd->argv[1] && cmd->argv[2])
		return (*cmd->exitcode = error_msg("exit: too many arguments"), 1);
	if (cmd->argv[1] == NULL)
	{
		*cmd->exitcode = exit_code;
	}
	else if (is_valid_numeric(cmd->argv[1]))
	{
		exit_code = atoi(cmd->argv[1]);
		*cmd->exitcode = exit_code;
	}
	else
	{
		printf("exit: numeric argument required\n");
		*cmd->exitcode = EXIT_ERROR_CODE;
		exit_code = EXIT_ERROR_CODE;
	}
	//free memory
	exit(exit_code);
	return (0);
}
