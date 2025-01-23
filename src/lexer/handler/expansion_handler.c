/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_handler.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:40:42 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/23 11:49:37 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*handle_special_param(char *str, int *pos, t_quote_state state)
{
	if (str[*pos + 1] == '?'
		&& (state.quote_char != '\'' || !state.in_quote))
	{
		(*pos)++;
		return (ft_itoa(g_exit_status));
	}
	return (NULL);
}

static char	*expand_var_name(char *str, int start, int len)
{
	char	*var_name;
	char	*value;

	var_name = ft_substr(str, start, len);
	if (!var_name)
		return (NULL);
	value = getenv(var_name);
	free(var_name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*get_var_value(char *str, int *pos, t_quote_state state)
{
	char	*value;
	int		start;
	int		len;

	if (state.quote_char == '\'')
		return (ft_strdup("$"));
	value = handle_special_param(str, pos, state);
	if (value)
		return (value);
	start = *pos + 1;
	len = 0;
	while (str[start + len] && is_valid_var_char(str[start + len]))
		len++;
	if (len == 0)
		return (ft_strdup("$"));
	*pos = start + len - 1;
	return (expand_var_name(str, start, len));
}
