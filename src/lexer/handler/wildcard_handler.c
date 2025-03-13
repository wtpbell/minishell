/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard_handler.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/30 11:15:13 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/13 18:41:56 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	has_wildcard(const char *str)
{
	int		i;
	int		in_single_quote;
	int		in_double_quote;

	if (!str)
		return (0);
	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (str[i] == '*' && !in_single_quote && !in_double_quote)
			return (1);
		i++;
	}
	return (0);
}

t_token	*handle_wildcard_token(const char *str)
{
	t_token_type	type;

	if (!str)
		return (NULL);
	type = TOKEN_WILDCARD;
	return (create_token(ft_strdup(str), type));
}

static int	handle_star(const char *pattern, t_match_state *state)
{
	if (pattern[state->i] == '*')
	{
		state->star_idx = state->i;
		state->str_star_idx = state->j;
		(state->i)++;
		return (1);
	}
	else if (state->star_idx != -1)
	{
		state->i = state->star_idx + 1;
		(state->str_star_idx)++;
		state->j = state->str_star_idx;
		return (1);
	}
	return (0);
}

int	match_pattern(const char *pattern, const char *string)
{
	t_match_state	state;

	state.i = 0;
	state.j = 0;
	state.star_idx = -1;
	state.str_star_idx = -1;
	while (string[state.j])
	{
		if (pattern[state.i] && (pattern[state.i] == string[state.j]
				|| pattern[state.i] == '?'))
		{
			state.i++;
			state.j++;
		}
		else if (handle_star(pattern, &state))
			continue ;
		else
			return (0);
	}
	while (pattern[state.i] == '*')
		state.i++;
	return (pattern[state.i] == '\0');
}

char	*handle_special_wildcard(t_tokenizer *tokenizer)
{
	char	*result;

	result = ft_strdup("*");
	if (!result)
		return (NULL);
	tokenizer->position++;
	return (result);
}
