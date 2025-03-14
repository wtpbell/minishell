/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_redir.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 12:56:28 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/14 14:41:29 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "parser.h"
#include "common.h"

static void	perform_dup2(int fd, int redir_fd)
{
	if (dup2(fd, redir_fd) == -1)
	{
		error("dup2 failed", NULL);
		close(fd);
		set_exit_status(1);
		return ;
	}
	if (fd != redir_fd)
		close(fd);
}

void	handle_heredoc_redirection(t_redir *current_redir, int saved_fd[2])
{
	int	fd;

	if (!current_redir->heredoc_processed || !current_redir->heredoc_file)
		return ;
	fd = open(current_redir->heredoc_file, O_RDONLY);
	if (fd == -1)
	{
		error(current_redir->heredoc_file, NULL);
		set_exit_status(1);
		return ;
	}
	if (saved_fd[current_redir->fd] == -1)
		saved_fd[current_redir->fd] = dup(current_redir->fd);
	perform_dup2(fd, current_redir->fd);
}

void	handle_regular_redirection(t_redir *current_redir, \
			int saved_fd[2], bool error_)
{
	int	fd;

	if (!current_redir->file)
		return ;
	fd = open(current_redir->file, current_redir->flags, 0644);
	if (fd == -1)
	{
		if (error_)
			error(current_redir->file, NULL);
		set_exit_status(1);
		return ;
	}
	if (saved_fd[current_redir->fd] == -1)
		saved_fd[current_redir->fd] = dup(current_redir->fd);
	perform_dup2(fd, current_redir->fd);
	set_exit_status(0);
}

bool	launch_redir(t_redir *current_redir, int saved_fd[2], bool error_)
{
	int	pre_status;

	if (current_redir->type == TOKEN_HEREDOC)
	{
		handle_heredoc_redirection(current_redir, saved_fd);
		return (get_exit_status() == 0);
	}
	else
	{
		pre_status = get_exit_status();
		handle_regular_redirection(current_redir, saved_fd, error_);
		return (get_exit_status() == pre_status);
	}
}

void	restore_redirection(int saved_fd[2])
{
	if (saved_fd[0] != -1)
	{
		dup2(saved_fd[0], STDIN_FILENO);
		close(saved_fd[0]);
		saved_fd[0] = -1;
	}
	if (saved_fd[1] != -1)
	{
		dup2(saved_fd[1], STDOUT_FILENO);
		close(saved_fd[1]);
		saved_fd[1] = -1;
	}
}
