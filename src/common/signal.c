/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 14:41:36 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/15 21:17:13 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "executor.h"
#include <signal.h>
#include <unistd.h>

int	setup_signal(int signum, void (*handler)(int))
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	if (sigaction(signum, &sa, NULL) == -1)
	{
		ft_putendl_fd("sigaction() error", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

void	signals_shell(void)
{
	setup_signal(SIGINT, interactive_handler);
	setup_signal(SIGQUIT, SIG_IGN);
	setup_signal(SIGTERM, term_handler);
	signal_clear_all();
}

void	signals_child(void)
{
	setup_signal(SIGINT, SIG_DFL);
	setup_signal(SIGQUIT, SIG_DFL);
	setup_signal(SIGTERM, SIG_DFL);
	signal_clear_all();
}

void	signals_heredoc(void)
{
	setup_signal(SIGINT, heredoc_handler);
	setup_signal(SIGQUIT, SIG_IGN);
	setup_signal(SIGTERM, term_handler);
	signal_clear_all();
}
