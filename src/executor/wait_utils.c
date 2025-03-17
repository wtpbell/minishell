/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wait_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/06 23:00:05 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/15 21:17:33 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "common.h"
#include <fcntl.h>

static void	track_termination_signal(int sig)
{
	if (sig == SIGINT)
		signal_set(SIG_RECEIVED_INT);
	else if (sig == SIGTERM)
		signal_set(SIG_RECEIVED_TERM);
	else if (sig == SIGQUIT)
		signal_set(SIG_RECEIVED_QUIT);
}

int	process_exit_status(int status_)
{
	int	sig;

	if (WIFEXITED(status_))
		return (WEXITSTATUS(status_));
	else if (WIFSIGNALED(status_))
	{
		sig = WTERMSIG(status_);
		if (sig == SIGTERM)
			return (signal_clear_all(), 0);
		track_termination_signal(sig);
		return (128 + sig);
	}
	return (EXIT_FAILURE);
}

int	wait_for_child(void)
{
	int	status_;

	wait(&status_);
	return (process_exit_status(status_));
}

int	wait_for_pid(pid_t pid)
{
	int	status_;

	waitpid(pid, &status_, 0);
	return (process_exit_status(status_));
}

void	wait_for_remain(void)
{
	while (wait(NULL) > 0)
		;
}
