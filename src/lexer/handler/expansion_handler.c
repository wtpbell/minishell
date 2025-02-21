/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_handler.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:40:42 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/21 09:52:46 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "env.h"

/* Check environment variable characters
** (alphabets, numbers, _ starting with $) */
int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*expand_exit_status(void)
{
	extern int	g_exit_status;
	char		*expanded;

	expanded = ft_itoa(g_exit_status);
	if (!expanded)
		return (NULL);
	return (expanded);
}

char	*get_env_var_value(char *str, int start, int len)
{
	char	*var_name;
	char	*value;

	var_name = ft_substr(str, start, len);
	if (!var_name)
		return (NULL);
	value = get_env_value(*get_env_list(), var_name);
	free(var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

/* Handles environment variable expansion */
char	*get_var_value(char *str, int *pos, t_quote_state state)
{
	if (state.quote_char == '\'' && state.in_quote)
		return (ft_strdup("$"));
	if (str[*pos + 1] == '{')
		return (handle_braced_expansion(str, pos, state));
	return (handle_special_param(str, pos, state));
}
