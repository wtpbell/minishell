/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_heredoc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 10:15:49 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/27 17:53:34 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "common.h"

//strace -f bash -c
static char	*gen_filename(void)
{
	static int	heredoc_count = 1;
	char		*filename;
	char		*index_str;

	index_str = mem_itoa(heredoc_count++);
	if (!index_str)
		return (NULL);
	filename = mem_strjoin("/tmp/heredoc_", index_str);
	free_alloc(index_str);
	index_str = NULL;
	return (filename);
}

static int	process_line(char *line, char *delimiter, int fd)
{
	size_t	len;

	if (!line)
	{
		error_heredoc(delimiter);
		return (0);
	}
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (0);
	}
	if (len > 0)
	{
		write(fd, line, len);
		write(fd, "\n", 1);
	}
	free(line);
	return (1);
}

static char	*process_heredoc(char *delimiter)
{
	char	*filename;
	int		fd;
	char	*line;
	int		continue_reading;

	filename = gen_filename();
	if (!filename)
		return (NULL);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		error("open heredoc", NULL);
		return (free_alloc(filename), filename = NULL, NULL);
	}
	while (1)
	{
		if (get_exit_status() == 130)
			break ;
		line = readline("heredoc> ");
		continue_reading = process_line(line, delimiter, fd);
		if (continue_reading == 0)
			break ;
	}
	close(fd);
	return (filename);
}

static void	cleanup_temp(t_redir *current, char *temp_file)
{
	if (!temp_file)
		return ;
	if (*heredoc_error() != -1)
		unlink(temp_file);
	if (current->file && current->file != temp_file)
		free(current->file);
	current->file = temp_file;
}

void	handle_all_heredocs(t_redir *redir, int saved_fd[2])
{
	t_redir	*current;
	char	*temp_file;

	current = redir;
	if (saved_fd[0] == -1)
		saved_fd[0] = dup(STDIN_FILENO);
	signal(SIGINT, heredoc_signals);
	*heredoc_error() = -1;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			temp_file = process_heredoc(current->file);
			cleanup_temp(current, temp_file);
		}
		current = current->next;
	}
	signal(SIGINT, SIG_DFL);
}
