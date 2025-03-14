/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 14:41:36 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/14 17:23:51 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "executor.h"
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t g_signal = SIG_NONE;

static void	interrupt_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_exit_status(1);
	signal_set(SIG_RECEIVED_INT);
	signal(SIGINT, interrupt_handler);
}

void	interrupt_w_nl(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	set_exit_status(1);
	signal_set(SIG_RECEIVED_INT);
	signal(SIGINT, interrupt_w_nl);
}

void	interrput_silence(int sig)
{
	(void)sig;
	set_exit_status(1);
	signal_set(SIG_RECEIVED_INT);
	signal(SIGINT, interrput_silence);
}

static void kill_handle(int sig)
{
	(void)sig;
	set_exit_status(0);
	signal_set(SIG_RECEIVED_TERM);
	signal(SIGTERM, kill_handle);
}

void	heredoc_signals(int sig)
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
	signal(SIGINT, heredoc_signals);
}

void	signals_init(void)
{
	sig_t	error;

	g_signal = SIG_NONE;
	if (error == SIG_ERR)
		ft_putendl_fd("signal() error", STDERR_FILENO);
	error = signal(SIGQUIT, SIG_IGN);
	if (error == SIG_ERR)
		ft_putendl_fd("signal() error", STDERR_FILENO);
	error = signal(SIGTERM, kill_handle);
	if (error == SIG_ERR)
		ft_putendl_fd("signal() error", STDERR_FILENO);
}
