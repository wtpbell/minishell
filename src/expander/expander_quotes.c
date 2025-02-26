/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_quotes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/26 14:15:38 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/26 15:25:03 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"

/* Handle quote characters in expansion */
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

/* Process a single character in the string */
static char	*process_string_char(char c, char *result)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(&c, 0, 1);
	tmp2 = ft_strjoin(result, tmp);
	free(tmp);
	free(result);
	return (tmp2);
}

/* Process expansion part when '$' is found */
static char	*process_expansion(const char *arg, int *i, char *result,
			t_quote_type current_quote)
{
	char	*tmp;
	char	*tmp2;
	char	*expanded;
	t_env	*env_list;

	env_list = *get_env_list();
	tmp = ft_substr(arg, 0, *i);
	tmp2 = ft_strjoin(result, tmp);
	free(tmp);
	free(result);
	result = tmp2;
	expanded = process_dollar(arg, i, env_list, current_quote);
	tmp = ft_strjoin(result, expanded);
	free(expanded);
	free(result);
	return (tmp);
}

/* Handle escape characters and expansions in string */
static char	*process_escapes_and_expansion(const char *arg, int *i,
			char *result, t_quote_type current_quote)
{
	if (arg[*i] == '\\')
	{
		if (arg[*i + 1] && (arg[*i + 1] == '$' || arg[*i + 1] == '\"'
				|| arg[*i + 1] == '\\') && current_quote != QUOTE_SINGLE)
		{
			result = process_string_char('\\', result);
			result = process_string_char(arg[*i + 1], result);
			*i += 2;
			return (result);
		}
	}
	else if (arg[*i] == '$' && current_quote != QUOTE_SINGLE)
	{
		if (*i > 0 && arg[*i - 1] == '\\')
			result = process_string_char('$', result);
		else
		{
			result = process_expansion(arg, i, result, current_quote);
			return (result);
		}
	}
	else
		result = process_string_char(arg[*i], result);
	(*i)++;
	return (result);
}

char	*handle_expansion(t_tokenizer *tokenizer, const char *arg)
{
	int				i;
	char			*result;
	t_quote_type	current_quote;

	(void)*tokenizer;
	if (!arg)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	current_quote = QUOTE_NONE;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
		{
			handle_quote_char(arg[i], &current_quote);
			result = process_string_char(arg[i], result);
			i++;
		}
		else
			result = process_escapes_and_expansion(arg, &i, result,
					current_quote);
	}
	return (result);
}
