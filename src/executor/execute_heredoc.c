/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_heredoc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 10:15:49 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/16 17:23:46 by bewong        ########   odam.nl         */
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
		free(*filename);
		*filename = NULL;
		return (-1);
	}
	return (fd);
}

static void	read_heredoc_lines(t_heredoc_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (get_exit_status() == 130)
		{
			free(line);
			break ;
		}
		data->line = line;
		if (process_line(data) == 0)
			break ;
		free(line);
	}
}

static char	*process_heredoc(char *delimiter, t_quote_type quote_type)
{
	char			*filename;
	int				fd;
	t_env			*env_list;
	t_heredoc_data	data;

	env_list = *get_env_list();
	fd = open_heredoc_file(&filename);
	if (fd == -1)
		return (NULL);
	data = (t_heredoc_data){
		.line = NULL,
		.delimiter = delimiter,
		.fd = fd,
		.env_list = env_list,
		.quote_type = quote_type,
		.should_expand = (quote_type == QUOTE_NONE)
	};
	read_heredoc_lines(&data);
	close(fd);
	return (filename);
}

static void	process_heredocs(t_redir *redir)
{
	t_redir			*current;
	char			*temp_file;
	t_quote_type	quote_type;

	current = redir;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC && !current->heredoc_processed)
		{
			quote_type = current->quote_type;
			temp_file = process_heredoc(current->delimiter, quote_type);
			if (temp_file)
			{
				if (current->heredoc_file)
					free(current->heredoc_file);
				current->heredoc_file = temp_file;
				current->heredoc_processed = 1;
			}
			else
				break ;
		}
		current = current->next;
	}
}

void	handle_all_heredocs(t_redir *redir, int saved_fd[2])
{
	if (saved_fd[0] == -1)
		saved_fd[0] = dup(STDIN_FILENO);
	signals_heredoc();
	process_heredocs(redir);
	if (saved_fd[0] != -1)
	{
		if (dup2(saved_fd[0], STDIN_FILENO) == -1)
			perror("Failed to redirect stdin to heredoc");
		close(saved_fd[0]);
	}
}
