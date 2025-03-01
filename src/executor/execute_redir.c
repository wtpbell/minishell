/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_redir.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 12:56:28 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/01 13:18:34 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "parser.h"

static void	perform_dup2(int fd, int redir_fd)
{
	if (dup2(fd, redir_fd) == -1)
	{
		close(fd);
		error("dup2 failed", NULL);
		set_exit_status(1);
		return ;
	}
	close(fd);
}

static int	handle_heredoc_redirection(t_redir *redir, int saved_fd[2])
{
	int	fd;

	if (!redir->heredoc_file)
		return (-1);
	fd = open(redir->heredoc_file, O_RDONLY);
	if (fd == -1)
	{
		error(redir->heredoc_file, NULL);
		set_exit_status(1);
		return (-1);
	}
	if (saved_fd[0] == -1)
		saved_fd[0] = dup(STDIN_FILENO);
	return (fd);
}

static int	handle_regular_redirection(t_redir *redir,
				int saved_fd[2], int redir_fd)
{
	int	fd;

	if (!redir->file)
		return (-1);
	fd = open(redir->file, get_flags(redir->type), 0644);
	if (fd == -1)
	{
		error(redir->file, NULL);
		set_exit_status(1);
		return (-1);
	}
	if (saved_fd[redir_fd] == -1)
		saved_fd[redir_fd] = dup(redir_fd);
	return (fd);
}

void	launch_redir(t_redir *current_redir, int saved_fd[2])
{
	int	fd;
	int	redir_fd;

	redir_fd = get_redir_fd(current_redir->type);
	if (current_redir->type == TOKEN_HEREDOC)
		fd = handle_heredoc_redirection(current_redir, saved_fd);
	else
		fd = handle_regular_redirection(current_redir, saved_fd, redir_fd);
	if (fd != -1)
	{
		perform_dup2(fd, redir_fd);
		close(fd);
	}
}

void	restore_redirection(int saved_fd[2])
{
	if (saved_fd[0] != -1)
	{
		dup2(saved_fd[0], STDIN_FILENO);
		close(saved_fd[0]);
	}
	if (saved_fd[1] != -1)
	{
		dup2(saved_fd[1], STDOUT_FILENO);
		close(saved_fd[1]);
	}
}
