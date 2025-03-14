/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_dollar.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 14:46:46 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/14 09:37:47 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"

static int	is_exit_status_pattern(const char *arg, int pos)
{
	if (!arg || pos <= 0)
		return (0);
	if (arg[pos] != '$')
		return (0);
	if (arg[pos + 1] != '?')
		return (0);
	if (arg[pos + 2] != '\'')
		return (0);
	if (arg[pos - 1] != '\'')
		return (0);
	return (1);
}

char	*handle_dollar_sign(const char *arg, int *i,
	char *result, t_quote_type current_quote)
{
	if (arg[*i] == '$')
		result = process_expansion(arg, i, result, current_quote);
	return (result);
}

char	*handle_regular_char(const char *arg, int *i, char *result)
{
	result = process_string_char(arg[*i], result);
	(*i)++;
	return (result);
}

char	*handle_escape_char(const char *arg, int *i,
			char *result, t_quote_type current_quote)
{
	if (arg[*i] == '\\')
	{
		if (arg[*i + 1] && (arg[*i + 1] == '$' || arg[*i + 1] == '\"'
				|| arg[*i + 1] == '\\') && current_quote != QUOTE_SINGLE)
		{
			result = process_string_char(arg[*i + 1], result);
			*i += 2;
		}
		else
		{
			result = process_string_char(arg[*i], result);
			(*i)++;
		}
	}
	return (result);
}

char	*handle_single_quote_dollar(const char *arg, int *i,
			char *result, t_quote_type current_quote)
{
	if (current_quote == QUOTE_SINGLE && arg[*i] == '$')
	{
		if (is_exit_status_pattern(arg, *i))
			return (handle_exit_status(i, result));
		result = process_string_char(arg[*i], result);
		(*i)++;
	}
	return (result);
}
