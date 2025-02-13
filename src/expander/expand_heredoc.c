/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_heredoc.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/13 17:11:17 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/13 18:03:02 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "minishell.h"
#include "parser.h"
#include "expander.h"

static char	*append_var_heredocs(char *appended, char *str, int *pos)
{
	char	*var;
	char	*tmp;
	int		i;

	i = 0;
	var = NULL;
	var = expand_var(str, &i);
	(*pos) += i;
	if (!appended)
		return (var);
	if (!var)
		return (free_alloc(appended), NULL);
	if (!appended)
		return (var);
	tmp = mem_strjoin(appended, var);
	free_alloc(appended);
	free_alloc(var);
	return (tmp);
}

static	char *append_regular_heredocs(char *appended, char *str, int *pos, char *set)
{
	char	*tmp;
	char	*result;
	int		i;

	i = 0;
	while (str[i] && !ft_strchr(set, str[i]))
		i++;
	tmp = NULL;
	if (i > 0)
		tmp = mem_strndup(str, i);
	if (!tmp)
		return (free_alloc(appended), NULL);
	(*pos) += i;
	if (!appended)
		return (tmp);
	result = mem_strjoin(appended, tmp);
	free_alloc(appended);
	free_alloc(tmp);
	return (result);
}

static char	*read_n_expand(int heredoc_fd)
{
	char	*content;
	char	*line;
	int		i;

	content = NULL;
	line = get_next_line(heredoc_fd);
	while (line)
	{
		i = 0;
		while(line[i])
		{
			if (line[i] == '$')
				content = append_var_heredocs(content, line + i, &i);
			else
				content = append_regular_heredocs(content, line + i, &i, "$");
		}
		free_alloc(line);
		line = get_next_line(heredoc_fd);
	}
	return (content);
}

void	expand_heredoc(t_redirection *r)
{
	int		heredoc_fd;
	char	*content;

	if (r->type != TOKEN_HEREDOC)
		return ;
	heredoc_fd = open(r->file, O_RDONLY , 0644);
	if (heredoc_fd == -1)
		return (error("open heredoc", NULL), free_all_memory(), exit(1));
	content = read_n_expand(heredoc_fd);
	close(heredoc_fd);
	if (content)
	{
		heredoc_fd = open(r->file, O_WRONLY, 0644);
		if (heredoc_fd == -1)
			return (error("open heredoc", NULL), free_all_memory(), exit(1));
		write(heredoc_fd, content, ft_strlen(content));
		close(heredoc_fd);
		free_alloc(content);
	}
}
