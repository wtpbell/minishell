/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_handler.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:40:42 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/30 17:21:55 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** Check environment variable characters
** (alphabets, numbers, _ starting with $)
*/
static int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/*
** Extract environment variable names and return their values
** Returns an empty string for non-existent variables
*/
static char	*handle_simple_expansion(char *str, int *pos, t_quote_state state)
{
	int		start;
	int		len;
	char	*var_name;
	char	*value;

	(void)state;
	start = *pos + 1;
	len = 0;
	while (str[start + len] && is_valid_var_char(str[start + len]))
		len++;
	if (len == 0)
		return (ft_strdup("$"));
	*pos = start + len - 1;
	var_name = ft_substr(str, start, len);
	if (!var_name)
		return (NULL);
	value = handle_extended_expansion(var_name, NULL, NULL);
	free(var_name);
	if (!value)
		return (ft_strdup(""));
	return (value);
}

static char	*handle_special_param(char *str, int *pos, t_quote_state state)
{
	char	*param;
	char	*result;

	if (str[*pos + 1] == '?' || str[*pos + 1] == '$' || str[*pos + 1] == '#')
	{
		param = ft_substr(str, *pos + 1, 1);
		if (!param)
			return (NULL);
		result = expand_special_param(param);
		free(param);
		(*pos)++;
		return (result);
	}
	return (handle_simple_expansion(str, pos, state));
}

/*
** Handles environment variable expansion.
** It is responsible for expanding variables
** that start with $ to their actual value. */
char	*get_var_value(char *str, int *pos, t_quote_state state)
{
	if (state.quote_char == '\'' && state.in_quote)
		return (ft_strdup("$"));
	if (str[*pos + 1] == '{')
		return (handle_braced_expansion(str, pos, state));
	return (handle_special_param(str, pos, state));
}
