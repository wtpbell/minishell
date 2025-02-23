/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_param_handler.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 09:46:13 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/21 09:50:44 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "env.h"

/* Extract environment variable names and return their values */
static char	*handle_simple_expansion(char *str, int *pos, t_quote_state state)
{
	int	start;
	int	len;

	if (state.quote_char == '\'' && state.in_quote)
		return (ft_strdup("$"));
	if (!str || !pos)
		return (NULL);
	if (str[*pos + 1] == '?')
	{
		(*pos)++;
		return (expand_exit_status());
	}
	start = *pos + 1;
	len = 0;
	while (str[start + len] && is_valid_var_char(str[start + len]))
		len++;
	if (len == 0)
		return (ft_strdup("$"));
	*pos = start + len - 1;
	return (get_env_var_value(str, start, len));
}

/* Handles special parameter expansion */
char	*handle_special_param(char *str, int *pos, t_quote_state state)
{
	if (state.quote_char == '\'' && state.in_quote)
		return (ft_strdup("$"));
	if (str[*pos + 1] == '$' || str[*pos + 1] == '#')
	{
		(*pos)++;
		return (ft_strdup(&str[*pos]));
	}
	return (handle_simple_expansion(str, pos, state));
}
