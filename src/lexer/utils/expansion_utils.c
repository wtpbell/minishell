/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 11:44:43 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/23 17:28:38 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Process variable expansion */
static char	*process_var_expansion(char *result, char *word,
	int *i, t_quote_state state)
{
	char	*var_value;

	var_value = get_var_value(word, i, state);
	if (!var_value)
		return (result);
	result = ft_strjoin_free(result, var_value);
	free(var_value);
	return (result);
}

/* Add a single character to the result string */
static char	*process_char(char *result, char c)
{
	return (ft_strjoin_char(result, c));
}

/* Check if the variable needs to be expanded */
static int	should_expand_var(char c, char next_c, t_quote_state state)
{
	return (c == '$' && next_c
		&& (state.quote_char != '\'' || !state.in_quote));
}

/* Handle string expansion */
char	*handle_expansion(t_tokenizer *tokenizer, char *word)
{
	char			*result;
	t_quote_state	state;
	int				i;

	if (!word)
		return (NULL);
	result = ft_strdup("");
	i = -1;
	while (word[++i])
	{
		state = get_quote_state(tokenizer);
		if (word[i] == '\'' || word[i] == '\"')
			handle_quote(tokenizer);
		else if (should_expand_var(word[i], word[i + 1], state))
			result = process_var_expansion(result, word, &i, state);
		else
			result = process_char(result, word[i]);
	}
	return (result);
}
