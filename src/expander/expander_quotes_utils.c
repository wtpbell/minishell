/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_quotes_utils.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 14:46:44 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/12 15:07:33 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"

void	handle_quote_char(char c, t_quote_type *current_quote)
{
	if (c == '\'' && *current_quote != QUOTE_DOUBLE)
	{
		if (*current_quote == QUOTE_SINGLE)
			*current_quote = QUOTE_NONE;
		else
			*current_quote = QUOTE_SINGLE;
	}
	else if (c == '\"' && *current_quote != QUOTE_SINGLE)
	{
		if (*current_quote == QUOTE_DOUBLE)
			*current_quote = QUOTE_NONE;
		else
			*current_quote = QUOTE_DOUBLE;
	}
}

char	*process_string_char(char c, char *result)
{
	char	buffer[2];
	char	*tmp;

	if (!result)
		return (NULL);
	buffer[0] = c;
	buffer[1] = '\0';
	tmp = ft_strjoin(result, buffer);
	free(result);
	return (tmp);
}

char	*process_expansion(const char *arg, int *i,
							char *result, t_quote_type current_quote)
{
	char	*tmp;
	char	*expanded;
	t_env	*env_list;

	env_list = *get_env_list();
	expanded = process_dollar(arg, i, env_list, current_quote);
	if (!expanded)
		return (NULL);
	tmp = ft_strjoin(result, expanded);
	free(expanded);
	free(result);
	return (tmp);
}

char	*process_escapes_and_expansion(const char *arg, int *i,
			char *result, t_quote_type *current_quote)
{
	if (!arg || !result || !i)
		return (NULL);
	result = handle_single_quote_dollar(arg, i, result, *current_quote);
	if ((size_t) * i >= ft_strlen(arg))
		return (result);
	if (arg[*i] == '\\')
		result = handle_escape_char(arg, i, result, *current_quote);
	else if (arg[*i] == '$')
		result = handle_dollar_sign(arg, i, result, *current_quote);
	else
		result = handle_regular_char(arg, i, result);
	return (result);
}

int	is_full_exit_status_pattern(const char *arg, int i)
{
	if (!arg)
		return (0);
	if (!arg[i] || !arg[i + 1] || !arg[i + 2] || !arg[i + 3])
		return (0);
	if (arg[i] == '\''
		&& arg[i + 1] == '$'
		&& arg[i + 2] == '?'
		&& arg[i + 3] == '\'')
		return (1);
	return (0);
}
