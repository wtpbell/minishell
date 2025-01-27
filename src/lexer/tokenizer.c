/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 14:36:18 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/27 08:49:15 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** Tokenise the input string
** Generate a list of associations by skipping spaces
   and converting operators/words to tokens
*/
t_token	*tokenize(char *input)
{
	t_tokenizer	tokenizer;
	t_token		*new_token;

	if (!input)
		return (NULL);
	init_tokenizer(&tokenizer, input);
	while (tokenizer.input[tokenizer.position])
	{
		tokenizer.position += skip_spaces(&tokenizer.input[tokenizer.position]);
		if (!tokenizer.input[tokenizer.position])
			break ;
		if (is_operator(&tokenizer.input[tokenizer.position]))
			new_token = handle_operator(&tokenizer);
		else
			new_token = handle_word(&tokenizer);
		if (!new_token)
			return (NULL);
		add_token(&tokenizer.head, new_token);
	}
	return (tokenizer.head);
}
