/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 14:36:18 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/04 10:32:10 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Check if the position is valid */
int	is_valid_position(t_tokenizer *tokenizer)
{
	return (tokenizer && tokenizer->input
		&& tokenizer->position >= 0
		&& tokenizer->position < (int)ft_strlen(tokenizer->input));
}

/* Tokenize the input */
t_token	*tokenize(char *input)
{
	t_tokenizer	tokenizer;
	t_token		*new_token;

	if (!input)
		return (NULL);
	init_tokenizer(&tokenizer, input);
	while (is_valid_position(&tokenizer))
	{
		tokenizer.position
			+= ft_skipspaces(&tokenizer.input[tokenizer.position]);
		if (!is_valid_position(&tokenizer))
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
