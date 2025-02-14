/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_handler.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:32:09 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/14 11:03:29 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Skip spaces */
static void	skip_spaces(t_tokenizer *tokenizer)
{
	while (tokenizer->input[tokenizer->position]
		&& ft_isspace(tokenizer->input[tokenizer->position]))
		tokenizer->position++;
}

/* Extract quoted content */
static char	*extract_quoted_content(t_tokenizer *tokenizer, char quote)
{
	int		start;
	char	*content;

	tokenizer->position++;
	start = tokenizer->position;
	while (tokenizer->input[tokenizer->position]
		&& tokenizer->input[tokenizer->position] != quote)
		tokenizer->position++;
	if (!tokenizer->input[tokenizer->position])
		return (NULL);
	content = ft_substr(tokenizer->input, start, tokenizer->position - start);
	tokenizer->position++;
	return (content);
}

/* Extract word */
static char	*extract_word(t_tokenizer *tokenizer)
{
	int		start;
	char	*word;

	start = tokenizer->position;
	while (tokenizer->input[tokenizer->position]
		&& !ft_isspace(tokenizer->input[tokenizer->position])
		&& !is_operator(&tokenizer->input[tokenizer->position])
		&& !is_quote(tokenizer->input[tokenizer->position]))
		tokenizer->position++;
	word = ft_substr(tokenizer->input, start, tokenizer->position - start);
	if (!word)
		return (NULL);
	return (word);
}

/* Handle word */
t_token	*handle_word(t_tokenizer *tokenizer)
{
	char	*content;
	t_token	*token;

	if (!tokenizer || !tokenizer->input)
		return (NULL);
	skip_spaces(tokenizer);
	if (is_quote(tokenizer->input[tokenizer->position]))
	{
		content = extract_quoted_content(tokenizer,
			tokenizer->input[tokenizer->position]);
		if (!content)
			return (NULL);
		return (create_token(content, TOKEN_WORD));
	}
	content = extract_word(tokenizer);
	if (!content)
		return (NULL);
	if (has_wildcard(content))
		token = handle_wildcard_token(content);
	else
		token = create_token(ft_strdup(content), TOKEN_WORD);
	if (!token)
		return (free(content),(NULL));
	free(content);
	return (token);
}
