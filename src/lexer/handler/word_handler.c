/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_handler.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:32:09 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/04 16:56:32 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Check word token termination conditions (meets null, operator, space) */
static int	should_stop_word(t_tokenizer *tokenizer)
{
	char	current;

	current = tokenizer->input[tokenizer->position];
	if (!current)
		return (1);
	if (!is_in_quotes(tokenizer)
		&& (is_operator(&tokenizer->input[tokenizer->position])
			|| ft_isspace(tokenizer->input[tokenizer->position])))
		return (1);
	return (0);
}

static int	has_wildcard(const char *word)
{
	return (word && ft_strchr(word, '*') != NULL);
}

static t_token	*create_word_token(char *word, t_tokenizer *tokenizer)
{
	if (!word)
		return (NULL);
	if (tokenizer->in_quote)
		return (create_token(word, TOKEN_WORD));
	if (word[0] == '$')
		return (create_token(word, TOKEN_VAR));
	if (has_wildcard(word))
		return (create_token(word, TOKEN_WILDCARD));
	return (create_token(word, TOKEN_WORD));
}

/*
** Generate word tokens
** Extract strings, handling quotes and extensions
*/
t_token	*handle_word(t_tokenizer *tokenizer)
{
	int		start;
	char	*word;

	if (!validate_quotes(tokenizer->input + tokenizer->position))
		return (NULL);
	start = tokenizer->position;
	while (tokenizer->input[tokenizer->position])
	{
		if (is_quote(tokenizer->input[tokenizer->position]))
			handle_quote(tokenizer);
		else if (should_stop_word(tokenizer))
			break ;
		tokenizer->position++;
	}
	word = ft_substr(tokenizer->input, start,
			tokenizer->position - start);
	if (!word)
		return (NULL);
	return (create_word_token(word, tokenizer));
}
