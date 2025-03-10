/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wait_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/06 23:00:05 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/07 22:19:09 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include <fcntl.h>

int	wait_for_child(void)
{
	int	status_;

	wait(&status_);
	if (WIFEXITED(status_))
		return (WEXITSTATUS(status_));
	return (EXIT_FAILURE);
}

int	wait_for_pid(pid_t pid)
{
	int	status_;

	waitpid(pid, &status_, 0);
	if (WIFEXITED(status_))
		return (WEXITSTATUS(status_));
	else if (WIFSIGNALED(status_))
		return (128 + WTERMSIG(status_));
	return (EXIT_FAILURE);
}

void	wait_for_remain(void)
{
	while (wait(NULL) > 0)
		;
}
