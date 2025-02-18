/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_content_handler.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 15:19:39 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/18 15:24:32 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*handle_escaped_quote(t_tokenizer *tokenizer,
	char quote, int *start, char *result)
{
	char	*content;

	content = ft_substr(tokenizer->input, *start,
			tokenizer->position - *start);
	result = ft_strjoin_free(result, content);
	result = ft_strjoin_char(result, quote);
	tokenizer->position += 2;
	*start = tokenizer->position;
	return (result);
}

char	*extract_quote_content(t_tokenizer *tokenizer,
	char quote, int start)
{
	char	*content;
	char	*result;

	result = ft_strdup("");
	while (tokenizer->input[tokenizer->position]
		&& tokenizer->input[tokenizer->position] != quote)
	{
		if (tokenizer->input[tokenizer->position] == '\\'
			&& tokenizer->input[tokenizer->position + 1] == quote)
			result = handle_escaped_quote(tokenizer, quote, &start, result);
		else
			tokenizer->position++;
	}
	if (start < tokenizer->position)
	{
		content = ft_substr(tokenizer->input, start,
				tokenizer->position - start);
		result = ft_strjoin_free(result, content);
	}
	return (result);
}

char	*extract_quoted_content(t_tokenizer *tokenizer, char quote)
{
	int		start;
	char	*result;

	tokenizer->position++;
	start = tokenizer->position;
	result = extract_quote_content(tokenizer, quote, start);
	tokenizer->position++;
	return (result);
}
