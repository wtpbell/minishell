/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_handler.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:32:09 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/21 12:57:27 by spyun         ########   odam.nl         */
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

/* Analyze and create token */
static t_token	*analyze_and_create_token(char *content,
										t_tokenizer *tokenizer)
{
	t_token	*token;
	char	*expanded_content;
	int		should_expand;

	should_expand = (ft_strchr(content, '$')
			&& (!tokenizer->in_quote
				|| (tokenizer->in_quote && tokenizer->quote_char == '"')));
	if (should_expand)
	{
		expanded_content = handle_expansion(tokenizer, content);
		if (!expanded_content)
			return (free(content), NULL);
		token = create_token(expanded_content, TOKEN_WORD);
	}
	else if (has_wildcard(content))
		token = handle_wildcard_token(content);
	else
		token = create_token(ft_strdup(content), TOKEN_WORD);
	if (!token)
		return (free(content), NULL);
	free(content);
	return (token);
}

/* Handle word */
t_token	*handle_word(t_tokenizer *tokenizer)
{
	char	*content;

	if (!tokenizer || !tokenizer->input)
		return (NULL);
	skip_spaces(tokenizer);
	content = extract_word(tokenizer);
	if (!content)
		return (NULL);
	return (analyze_and_create_token(content, tokenizer));
}
