/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_quotes.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/26 14:15:38 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/14 09:46:59 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"

static char	*init_expansion(void)
{
	char	*result;

	result = ft_strdup("");
	return (result);
}

static void	process_quote_change(char quote_char, t_quote_type *current_quote,
	int *in_double_quotes)
{
	if (quote_char == '\"' && *current_quote == QUOTE_NONE)
		*in_double_quotes = 1;
	else if (quote_char == '\"' && *current_quote == QUOTE_DOUBLE)
		*in_double_quotes = 0;
	handle_quote_char(quote_char, current_quote);
}

static char	*handle_quotes(const char *arg, int *i, char *result,
	t_expansion_state *state)
{
	process_quote_change(arg[*i], &state->current_quote,
		&state->in_double_quotes);
	result = process_string_char(arg[*i], result);
	if (!result)
		return (NULL);
	(*i)++;
	return (result);
}

char	*handle_expansion_loop(const char *arg, char *result,
	t_expansion_state *state)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
			result = handle_quotes(arg, &i, result, state);
		else if (state->in_double_quotes && is_full_exit_status_pattern(arg, i))
			result = process_exit_status_in_dquotes(arg, &i, result);
		else
			result = process_escapes_and_expansion(arg, &i, result,
					&state->current_quote);
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*handle_expansion(t_tokenizer *tokenizer, const char *arg)
{
	char				*result;
	t_expansion_state	state;

	(void)tokenizer;
	if (!arg)
		return (NULL);
	result = init_expansion();
	if (!result)
		return (NULL);
	state.current_quote = QUOTE_NONE;
	state.in_double_quotes = 0;
	result = handle_expansion_loop(arg, result, &state);
	return (result);
}
