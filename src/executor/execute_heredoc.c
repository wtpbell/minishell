/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_heredoc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 10:15:49 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/03 14:09:02 by bewong        ########   odam.nl         */
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
		if (!line)
		{
			if (get_exit_status() != 130)
				error_heredoc(delimiter);
			break ;
		}
		data.line = line;
		data.delimiter = delimiter;
		data.fd = fd;
		data.env_list = env_list;
		data.should_expand = (quote_type == QUOTE_NONE);
		continue_reading = process_line(&data);
		if (continue_reading == 0)
			break ;
		// free(line);
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

// Function to process all heredocs
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

//Main function to handle all heredocs and restore stdin after
void	handle_all_heredocs(t_redir *redir, int saved_fd[2])
{
	if (saved_fd[0] == -1)
		saved_fd[0] = dup(STDIN_FILENO);
	signal(SIGINT, heredoc_signals);
	process_heredocs(redir);
	if (saved_fd[0] != -1)
	{
		dup2(saved_fd[0], STDIN_FILENO);
		close(saved_fd[0]);
	}
	signal(SIGINT, SIG_DFL);
}
