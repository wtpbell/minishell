/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/01 09:34:29 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/01 09:42:25 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expander.h"
#include "common.h"

char	*gen_filename(void)
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

int	write_expanded_line(char *expanded_line, int fd)
{
	size_t	len;

	len = ft_strlen(expanded_line);
	if (len > 0)
	{
		write(fd, expanded_line, len);
		write(fd, "\n", 1);
	}
	return (1);
}

int	process_line(t_heredoc_data *data)
{
	size_t	len;
	char	*expanded_line;

	if (!data->line)
	{
		error_heredoc(data->delimiter);
		return (0);
	}
	len = ft_strlen(data->line);
	if (len > 0 && data->line[len - 1] == '\n')
		data->line[len - 1] = '\0';
	if (ft_strcmp(data->line, data->delimiter) == 0)
		return (free(data->line), 0);
	if (data->should_expand)
		expanded_line = expand_heredoc_line(data->line, data->env_list);
	else
		expanded_line = data->line;
	write_expanded_line(expanded_line, data->fd);
	if (data->should_expand && expanded_line != data->line)
		free(expanded_line);
	else if (!data->should_expand)
		free(data->line);
	return (1);
}
