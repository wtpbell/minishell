/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_expander.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/01 09:35:02 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/12 15:09:28 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "expander.h"
#include "common.h"

static char	*join_expanded_part(char *result, char *expanded)
{
	char	*temp;

	temp = result;
	result = ft_strjoin(result, expanded);
	free(temp);
	free(expanded);
	return (result);
}

static char	*join_char_to_result(char *result, char c)
{
	char	*temp;
	char	c_str[2];

	c_str[0] = c;
	c_str[1] = '\0';
	temp = result;
	result = ft_strjoin(result, c_str);
	free(temp);
	return (result);
}

static char	*heredoc_handle_dollar_sign(char *line, int *i, char *result,
					t_env *env_list)
{
	char	*expanded;

	expanded = process_dollar(line, i, env_list, QUOTE_NONE);
	if (expanded)
	{
		result = join_expanded_part(result, expanded);
		if (!result)
			return (NULL);
	}
	return (result);
}

static char	*expand_line_loop(char *line, t_env *env_list, char *result)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			result = heredoc_handle_dollar_sign(line, &i, result, env_list);
			if (!result)
				return (NULL);
		}
		else
		{
			result = join_char_to_result(result, line[i]);
			if (!result)
				return (NULL);
			i++;
		}
	}
	return (result);
}

char	*expand_heredoc_line(char *line, t_env *env_list)
{
	char	*result;

	if (!line || !ft_strchr(line, '$'))
		return (line);
	result = ft_strdup("");
	if (!result)
		return (line);
	result = expand_line_loop(line, env_list, result);
	if (!result)
		return (line);
	return (result);
}
