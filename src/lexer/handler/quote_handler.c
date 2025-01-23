/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:30:29 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/23 11:38:44 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_in_quotes(t_tokenizer *tokenizer)
{
	return (tokenizer->in_quote);
}

static int	handle_nested_quote(t_tokenizer *tokenizer, char quote)
{
	if (!tokenizer->in_quote)
	{
		tokenizer->quote_char = quote;
		tokenizer->in_quote = 1;
		return (1);
	}
	if (tokenizer->quote_char == quote)
	{
		tokenizer->in_quote = 0;
		tokenizer->quote_char = 0;
		return (1);
	}
	return (0);
}

int	is_special_in_quotes(char c, char quote_char)
{
	if (quote_char == '"')
		return (c == '$' || c == '`' || c == '\\');
	return (0);
}

void	handle_quote(t_tokenizer *tokenizer)
{
	char	current;

	current = tokenizer->input[tokenizer->position];
	if (!handle_nested_quote(tokenizer, current))
	{
		tokenizer->position++;
	}
}

t_quote_state	get_quote_state(t_tokenizer *tokenizer)
{
	t_quote_state	state;

	state.in_quote = tokenizer->in_quote;
	state.quote_char = tokenizer->quote_char;
	return (state);
}
