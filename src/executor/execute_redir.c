/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_redir.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 12:56:28 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/28 23:15:08 by bewong        ########   odam.nl         */
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

void	launch_redir(t_redir *current_redir, int saved_fd[2])
{
	int	fd;

	if (!current_redir->file)
		return ;
	
	if (current_redir->type == TOKEN_HEREDOC)
	{
		fd = open(current_redir->file, current_redir->flags, 0644);
		if (saved_fd[current_redir->fd] == -1)
			saved_fd[current_redir->fd] = dup(current_redir->fd);
	}
	else
	{
		fd = open(current_redir->file, current_redir->flags, 0644);
		if (fd == -1)
		{
			error(current_redir->file, NULL);
			set_exit_status(1);
			return ;
		}
		if (saved_fd[current_redir->fd] == -1)
			saved_fd[current_redir->fd] = dup(current_redir->fd);
	}
	perform_dup2(fd, current_redir->fd);
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
