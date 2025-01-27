/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_expansion.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 16:55:50 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/23 17:00:39 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Calculates the length of the variable name following the dollar sign. */
static int	get_var_length(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

/* Adds the value of the environment variable to the result string. */
static char	*append_var_value(char *result, const char *var_name)
{
	char	*value;
	char	*temp;

	value = getenv(var_name);
	if (!value)
		return (result);
	temp = result;
	result = ft_strjoin(result, value);
	free(temp);
	return (result);
}

/* Handles variable expansion within a heredoc. */
char	*expand_heredoc_vars(char *line)
{
	int		i;
	int		var_len;
	char	*result;
	char	*var_name;

	result = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && line[i + 1] != ' ')
		{
			var_len = get_var_length(line + i + 1);
			if (var_len > 0)
			{
				var_name = ft_substr(line + i + 1, 0, var_len);
				result = append_var_value(result, var_name);
				free(var_name);
				i += var_len + 1;
				continue ;
			}
		}
		result = ft_strjoin_char(result, line[i]);
		i++;
	}
	return (result);
}
