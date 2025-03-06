/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_update.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/22 17:42:30 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/22 17:42:30 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "executor.h"
#include "common.h"

/*
	Exit Code		Meaning 							Example
	1				Catchall for general errors
	2				Misuse of shell builtins			empty_function()
	126				Command invoked cannot execute		/dev/null
	127				"command not found"					illegal_command (typo)
	128				Invalid argument to exit			kill -9 $PPID returns 137
	130				Script terminated by Control-C		Ctl-C
	255*			Exit status out of range			exit -1
*/

void	set_exit_status(int status)
{
	char	*status_;

	status_ = ft_itoa(status);
	if (status_)
	{
		set_env(*get_env_list(), "?", status_);
		free(status_);
	}
}

int	get_exit_status(void)
{
	char	*status_str;

	status_str = get_env_value(*get_env_list(), "?");
	if (!status_str)
		return (0);
	return (ft_atoi(status_str));
}
