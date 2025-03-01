/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_heredoc.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 10:15:49 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/01 09:14:41 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expander.h"
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

static char	*expand_heredoc_line(char *line, t_env *env_list)
{
	int				i;
	char			*result;
	char			*expanded;
	t_quote_type	quote_type;

	if (!line || !ft_strchr(line, '$'))
		return (line);
	result = ft_strdup("");
	if (!result)
		return (line);
	i = 0;
	quote_type = QUOTE_NONE;
	while (line[i])
	{
		if (line[i] == '$')
		{
			expanded = process_dollar(line, &i, env_list, quote_type);
			if (expanded)
			{
				char *temp = result;
				result = ft_strjoin(result, expanded);
				free(temp);
				free(expanded);
				if (!result)
					return (line);
			}
		}
		else
		{
			char *temp = result;
			char c[2] = {line[i], '\0'};
			result = ft_strjoin(result, c);
			free(temp);
			if (!result)
				return (line);
			i++;
		}
	}
	free(line);
	return (result);
}

static int	process_line(char *line, char *delimiter, int fd, t_env *env_list,
					int should_expand)
{
	size_t	len;
	char	*expanded_line;

	if (!line)
		return (error_heredoc(delimiter), 0);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (ft_strcmp(line, delimiter) == 0)
		return (free(line), 0);
	if (should_expand)
		expanded_line = expand_heredoc_line(line, env_list);
	else
		expanded_line = line;
	len = ft_strlen(expanded_line);
	if (len > 0)
	{
		write(fd, expanded_line, len);
		write(fd, "\n", 1);
	}
	if (should_expand && expanded_line != line)
		free(expanded_line);
	else if (!should_expand)
		free(line);
	return (1);
}

static char	*process_heredoc(char *delimiter, t_quote_type quote_type)
{
	char	*filename;
	int		fd;
	char	*line;
	int		continue_reading;
	t_env	*env_list;
	int		should_expand;

	env_list = *get_env_list();
	filename = gen_filename();
	if (!filename)
		return (NULL);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		error("open heredoc", NULL);
		return (free_alloc(filename), filename = NULL, NULL);
	}
	should_expand = (quote_type != QUOTE_SINGLE);
	while (1)
	{
		if (get_exit_status() == 130)
			break;
		line = readline("heredoc> ");
		continue_reading = process_line(line, delimiter, fd, env_list, should_expand);
		if (continue_reading == 0)
			break;
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
