/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_redir.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 12:56:28 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/25 14:35:25 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "parser.h"

static int	open_heredoc_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		error(file, NULL);
		set_exit_status(1);
	}
	return (fd);
}

static int	open_redir_file(char *file, int redir_type)
{
	int	fd;

	fd = open(file, get_flags(redir_type), 0644);
	if (fd == -1)
	{
		error(file, NULL);
		set_exit_status(1);
	}
	return (fd);
}

static void	perform_dup2(int fd, int redir_fd)
{
	if (dup2(fd, redir_fd) == -1)
	{
		close(fd);
		error("dup2 failed", NULL);
		set_exit_status(1);
	}
	close(fd);
}

void	launch_redir(t_redir *current_redir, int saved_fd[2])
{
	int	fd;
	int	redir_fd;

	if (!current_redir->file)
		return ;
	redir_fd = get_redir_fd(current_redir->type);
	if (current_redir->type == TOKEN_HEREDOC)
	{
		printf("Handling heredoc: %s\n", current_redir->file);
		fd = open_heredoc_file(current_redir->file);
		if (saved_fd[0] == -1)
			saved_fd[0] = dup(STDIN_FILENO);
	}
	else
	{
		fd = open_redir_file(current_redir->file, current_redir->type);
		if (saved_fd[redir_fd] == -1)
			saved_fd[redir_fd] = dup(redir_fd);
	}
	perform_dup2(fd, redir_fd);
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
