/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_init.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:28:38 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/12 11:35:50 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Initialize the tokenizer */
void	init_tokenizer(t_tokenizer *tokenizer, char *input)
{
	if (!tokenizer || !input)
		return ;
	tokenizer->input = input;
	tokenizer->head = NULL;
	tokenizer->position = 0;
	tokenizer->in_quote = 0;
	tokenizer->quote_char = 0;
	tokenizer->current_quote_type = QUOTE_NONE;
}
