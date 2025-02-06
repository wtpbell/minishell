/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_handler.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:32:09 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/06 09:14:02 by bewong        ########   odam.nl         */
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

/* Handles special characters and creates appropriate token type */
static t_token_type	get_word_token_type(char *word)
{
	if (!word || !*word)
		return (TOKEN_WORD);
	if (word[0] == '$')
		return (TOKEN_VAR);
	return (TOKEN_WORD);
}

/* Process word expansions and create appropriate token */
static t_token	*expand_word(t_tokenizer *tokenizer, char *word)
{
	char		*expanded;
	t_token		*token;

	if (!tokenizer || !word)
		return (NULL);
	if (tokenizer->in_quote)
	{
		token = create_token(word, get_word_token_type(word));
		if (!token)
			return (NULL);
		return (token);
	}
	expanded = handle_expansion(tokenizer, word);
	if (!expanded)
		return(free(word),(NULL));
	if (has_wildcard(expanded))
	{
		token = handle_wildcard_token(expanded);
		free(expanded);
		free(word);
		return (token);
	}
	token = create_token(expanded, get_word_token_type(expanded));
	if (!token)
		free(expanded);
	free(word);
	return (token);
}

/* Generate word tokens */
t_token	*handle_word(t_tokenizer *tokenizer)
{
	int		start;
	char	*content;

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
	content = ft_substr(tokenizer->input, start,
			tokenizer->position - start);
	if (!content)
		return (NULL);
	return (expand_word(tokenizer, content));
}
