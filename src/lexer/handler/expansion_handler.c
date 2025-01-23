/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_handler.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:40:42 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/23 11:35:17 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char *handle_special_param(char *str, int *pos)
{
	if (str[*pos + 1] == '?')
	{
		(*pos)++;
		return (ft_itoa(g_exit_status));
	}
	return (NULL);
}

static char *get_var_name(char *str, int *pos)
{
	char	*special_value;
	int		start;
	int		len;

	special_value = handle_special_param(str, pos);
	if (special_value)
		return (special_value);
	start = *pos + 1;
	len = 0;
	while (str[start + len] && is_valid_var_char(str[start + len]))
		len++;
	if (len == 0)
		return (NULL);
	*pos = start + len - 1;
	return (ft_substr(str, start, len));
}

static char	*get_env_value(char *var_name)
{
	char	*value;

	if (!var_name)
		return (NULL);
	value = getenv(var_name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*handle_expansion(char *word)
{
	char	*result;
	char	*var_name;
	char	*var_value;
	int		i;

	if (!word)
		return (NULL);
	result = ft_strdup("");
	i = -1;
	while (word[++i])
	{
		if (word[i] == '$' && word[i + 1])
		{
			var_name = get_var_name(word, &i);
			var_value = get_env_value(var_name);
			result = ft_strjoin_free(result, var_value);
			free(var_name);
			free(var_value);
		}
		else
			result = ft_strjoin_char(result, word[i]);
	}
	return (result);
}
