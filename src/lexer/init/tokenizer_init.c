/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_init.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:28:38 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/23 19:44:22 by spyun         ########   odam.nl         */
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
}
