/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 14:41:36 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/09 20:44:31 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "executor.h"
#include <signal.h>
#include <unistd.h>

/*
	Print a newline on Ctrl+C.
	rl_on_new_lin: Readline (if using) on a new line.
	rl_replace_line: Clear the current line.
	rl_redisplay: Redisplay the prompt.
	Set exit status for interrupt.
*/
static void	interrupt_handler(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	set_exit_status(1);
}

/* minimal feedback for external cmd execution */
void	interrupt_w_nl(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	set_exit_status(1);
}

void	interrput_silence(int sig)
{
	(void)sig;
	set_exit_status(1);
}

void	heredoc_signals(int sig)
{
	int	saved_stdin;

	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		perror("Failed to duplicate stdin before closing");
	close(STDIN_FILENO);
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		perror("Failed to redirect stdin to heredoc");
		close(saved_stdin);
	}
	close(saved_stdin);
	set_exit_status(130);
}

/* 
	Ignore SIGINT & SIGQUIT in parent process while it’s managing a subshell,
	preventing it from being interrupted while waiting for the child to finish.
*/
void	signals_init(void)
{
	sig_t	error;

	error = signal(SIGINT, interrupt_handler);
	if (error == SIG_ERR)
		ft_putendl_fd("signal() error", STDERR_FILENO);
	error = signal(SIGQUIT, SIG_IGN);
	if (error == SIG_ERR)
		ft_putendl_fd("signal() error", STDERR_FILENO);
}
