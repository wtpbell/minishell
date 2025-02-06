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
	1. Command Execution (exec_cmd)
		Update g_exit_status after execve.
	2. Pipelines (exec_pipe)
		Update g_exit_status based on the last command in the pipeline.
	3. Logical Operators (run_ctrl)
		Use g_exit_status to determine conditional execution.
	4. Redirections (run_redir)
		Update g_exit_status after applying redirections and running commands.
*/

/*
	Exit Code		Meaning 							Example
	1				Catchall for general errors
	2				Misuse of shell builtins			empty_function()
	126				Command invoked cannot execute		/dev/null
	127				"command not found"					illegal_command (typo)
	128				Invalid argument to exit			kill -9 $PPID returns 137 (128 + 9)
	130				Script terminated by Control-C		Ctl-C
	255*			Exit status out of range			exit -1
*/


void	set_exit_status(int status)
{
	g_exit_status = status;
	set_env(*get_env_list(), "?", mem_itoa(status));
}

int	get_exit_status(void)
{
	return (g_exit_status);
}
