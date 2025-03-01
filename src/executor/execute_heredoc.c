/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_heredoc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 10:15:49 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/01 11:51:31 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expander.h"
#include "common.h"

static int	open_heredoc_file(char **filename)
{
	int	fd;

	*filename = gen_filename();
	if (!*filename)
		return (-1);
	fd = open(*filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		error("open heredoc", NULL);
		free_alloc(*filename);
		*filename = NULL;
		return (-1);
	}
	return (fd);
}

static void	read_heredoc_lines(int fd, char *delimiter, t_env *env_list,
		t_quote_type quote_type)
{
	char			*line;
	int				continue_reading;
	t_heredoc_data	data;

	while (1)
	{
		if (get_exit_status() == 130)
			break ;
		line = readline("heredoc> ");
		data.line = line;
		data.delimiter = delimiter;
		data.fd = fd;
		data.env_list = env_list;
		data.should_expand = (quote_type == QUOTE_NONE);
		continue_reading = process_line(&data);
		if (continue_reading == 0)
			break ;
	}
}

static char	*process_heredoc(char *delimiter, t_quote_type quote_type)
{
	char	*filename;
	int		fd;
	t_env	*env_list;

	env_list = *get_env_list();
	fd = open_heredoc_file(&filename);
	if (fd == -1)
		return (NULL);
	read_heredoc_lines(fd, delimiter, env_list, quote_type);
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
	t_redir			*current;
	char			*temp_file;
	t_quote_type	quote_type;

	current = redir;
	if (saved_fd[0] == -1)
		saved_fd[0] = dup(STDIN_FILENO);
	signal(SIGINT, heredoc_signals);
	*heredoc_error() = -1;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			quote_type = current->quote_type;
			temp_file = process_heredoc(current->file, quote_type);
			cleanup_temp(current, temp_file);
		}
		current = current->next;
	}
	signal(SIGINT, SIG_DFL);
}
