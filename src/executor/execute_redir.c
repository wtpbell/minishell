/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_redir.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 12:56:28 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/02 20:52:28 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "parser.h"
#include "common.h"

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

// Function to handle heredoc redirection
static void	handle_heredoc_redirection(t_redir *current_redir, int saved_fd[2])
{
	int	fd;

	if (!current_redir->heredoc_processed || !current_redir->heredoc_file)
	{
		error("Heredoc not properly processed", NULL);
		return ;
	}
	fd = open(current_redir->heredoc_file, O_RDONLY);
	if (fd == -1)
	{
		error("Failed to open heredoc file", NULL);
		return ;
	}
	if (saved_fd[current_redir->fd] == -1)
		saved_fd[current_redir->fd] = dup(current_redir->fd);
	perform_dup2(fd, current_redir->fd);
	close(fd);
}

// Function to handle regular file redirection
static void	handle_regular_redirection(t_redir *current_redir, int saved_fd[2])
{
	int	fd;

	if (!current_redir->file)
		return ;
	fd = open(current_redir->file, current_redir->flags, 0644);
	if (fd == -1)
	{
		error(current_redir->file, NULL);
		set_exit_status(1);
		return ;
	}
	if (saved_fd[current_redir->fd] == -1)
		saved_fd[current_redir->fd] = dup(current_redir->fd);
	perform_dup2(fd, current_redir->fd);
	close(fd);
}

// Main function to launch the redirection
void	launch_redir(t_redir *current_redir, int saved_fd[2])
{
	if (current_redir->type == TOKEN_HEREDOC)
		handle_heredoc_redirection(current_redir, saved_fd);
	else
		handle_regular_redirection(current_redir, saved_fd);
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
