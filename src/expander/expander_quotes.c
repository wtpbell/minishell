/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_quotes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/26 14:15:38 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/12 14:18:05 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"

static void	handle_quote_char(char c, t_quote_type *current_quote)
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

static char	*process_string_char(char c, char *result)
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

static char	*process_expansion(const char *arg, int *i,
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

static char	*process_escapes_and_expansion(const char *arg, int *i,
			char *result, t_quote_type current_quote)
{
	char	*tmp;
	char	*exit_status;

	if (!arg || !result || !i)
		return (NULL);
	if (current_quote == QUOTE_SINGLE && arg[*i] == '$')
	{
		if (is_exit_status_pattern(arg, *i))
		{
			exit_status = ft_strdup(get_env_value(*get_env_list(), "?"));
			if (!exit_status)
				exit_status = ft_strdup("0");
			tmp = ft_strjoin(result, exit_status);
			free(exit_status);
			free(result);
			*i += 2;
			return (tmp);
		}
		result = process_string_char(arg[*i], result);
		(*i)++;
		return (result);
	}
	if (arg[*i] == '\\')
	{
		if (arg[*i + 1] && (arg[*i + 1] == '$' || arg[*i + 1] == '\"'
				|| arg[*i + 1] == '\\') && current_quote != QUOTE_SINGLE)
		{
			result = process_string_char(arg[*i + 1], result);
			*i += 2;
			return (result);
		}
		result = process_string_char(arg[*i], result);
		(*i)++;
	}
	else if (arg[*i] == '$')
	{
		result = process_expansion(arg, i, result, current_quote);
	}
	else
	{
		result = process_string_char(arg[*i], result);
		(*i)++;
	}
	return (result);
}

static int	is_full_exit_status_pattern(const char *arg, int i)
{
	if (!arg)
		return (0);
	if (!arg[i] || !arg[i+1] || !arg[i+2] || !arg[i+3])
		return (0);
	if (arg[i] == '\'' &&
		arg[i+1] == '$' &&
		arg[i+2] == '?' &&
		arg[i+3] == '\'')
		return (1);
	return (0);
}

char	*handle_expansion(t_tokenizer *tokenizer, const char *arg)
{
	int				i;
	char			*result;
	t_quote_type	current_quote;
	int				in_double_quotes;
	char			*tmp;
	char			*exit_status;

	(void)*tokenizer;
	if (!arg)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	current_quote = QUOTE_NONE;
	in_double_quotes = 0;

	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
		{
			if (arg[i] == '\"' && current_quote == QUOTE_NONE)
				in_double_quotes = 1;
			else if (arg[i] == '\"' && current_quote == QUOTE_DOUBLE)
				in_double_quotes = 0;

			handle_quote_char(arg[i], &current_quote);
			result = process_string_char(arg[i], result);
			if (!result)
				return (NULL);
			i++;
		}
		else
		{
			if (in_double_quotes && is_full_exit_status_pattern(arg, i))
			{
				result = process_string_char(arg[i], result);
				if (!result)
					return (NULL);
				i++;
				exit_status = ft_strdup(get_env_value(*get_env_list(), "?"));
				if (!exit_status)
					exit_status = ft_strdup("0");
				tmp = ft_strjoin(result, exit_status);
				free(exit_status);
				free(result);
				result = tmp;
				if (!result)
					return (NULL);
				i += 2;
				result = process_string_char(arg[i], result);
				if (!result)
					return (NULL);
				i++;
			}
			else
			{
				result = process_escapes_and_expansion(arg, &i, result, current_quote);
				if (!result)
					return (NULL);
			}
		}
	}
	return (result);
}
