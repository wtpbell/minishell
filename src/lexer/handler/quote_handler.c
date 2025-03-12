/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:30:29 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/12 11:48:18 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Update quote type based on current and previous quote */
static t_quote_type	update_quote_type(t_quote_type current_type, char new_quote)
{
	if (current_type == QUOTE_NONE)
		return (new_quote == '\'' ? QUOTE_SINGLE : QUOTE_DOUBLE);
	if (current_type == QUOTE_SINGLE && new_quote == '\'')
		return (QUOTE_NONE);
	if (current_type == QUOTE_DOUBLE && new_quote == '\"')
		return (QUOTE_NONE);
	if (current_type == QUOTE_NONE && new_quote == '\'')
		return (QUOTE_SINGLE);
	if (current_type == QUOTE_NONE && new_quote == '\"')
		return (QUOTE_DOUBLE);
	return (QUOTE_MIXED);
}

/* Handle nested quotes */
static int	handle_nested_quote(t_tokenizer *tokenizer, char quote)
{
	if (!is_valid_position(tokenizer))
		return (0);
	if (!tokenizer->in_quote)
	{
		tokenizer->quote_char = quote;
		tokenizer->in_quote = 1;
		tokenizer->current_quote_type
			= update_quote_type(tokenizer->current_quote_type, quote);
		return (1);
	}
	if (tokenizer->quote_char == quote)
	{
		tokenizer->in_quote = 0;
		tokenizer->quote_char = 0;
		return (1);
	}
	if (tokenizer->quote_char != quote)
	{
		tokenizer->current_quote_type = QUOTE_MIXED;
	}
	return (0);
}

/* Quote handling logic */
void	handle_quote(t_tokenizer *tokenizer)
{
	char	current;

	if (!is_valid_position(tokenizer))
	{
		tokenizer->position = -1;
		return ;
	}
	current = tokenizer->input[tokenizer->position];
	if (!handle_nested_quote(tokenizer, current))
		tokenizer->position++;
}
