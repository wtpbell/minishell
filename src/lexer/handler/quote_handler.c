/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:30:29 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/20 15:37:22 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	handle_quote(t_tokenizer *tokenizer)
{
	if (!tokenizer->in_quote)
	{
		tokenizer->quote_char = tokenizer->input[tokenizer->position];
		tokenizer->in_quote = 1;
	}
	else if (tokenizer->input[tokenizer->position] == tokenizer->quote_char)
	{
		tokenizer->in_quote = 0;
	}
}

int	is_in_quotes(t_tokenizer *tokenizer)
{
	return (tokenizer->in_quote);
}
