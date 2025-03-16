/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_handler.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/15 14:32:28 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/16 16:08:40 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "executor.h"
#include <signal.h>
#include <unistd.h>

void	interactive_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_exit_status(1);
	signal_set(SIG_RECEIVED_INT);
}

void	term_handler(int sig)
{
	(void)sig;
	signal_set(SIG_RECEIVED_TERM);
}

void	heredoc_handler(int sig)
{
	int	saved_stdin;

	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
	{
		perror("Failed to duplicate stdin before closing");
		close(saved_stdin);
	}
	close(STDIN_FILENO);
	close(saved_stdin);
	set_exit_status(130);
	signal_set(SIG_HEREDOC_INT);
}
