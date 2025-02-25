/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_content_handler.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 15:19:39 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/21 12:36:46 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*handle_escaped_quote(t_tokenizer *tokenizer,
	char quote, int *start, char *result)
{
	char	*content;
	char	*temp;

	content = ft_substr(tokenizer->input, *start,
			tokenizer->position - *start);
	if (!content)
		return (NULL);
	temp = ft_strjoin_free(result, content);
	free(content);
	if (!temp)
		return (NULL);
	result = ft_strjoin_char(temp, quote);
	free(temp);
	if (!result)
		return (NULL);
	tokenizer->position += 2;
	*start = tokenizer->position;
	return (result);
}

static char	*handle_remaining_content(t_tokenizer *tokenizer,
		char *result, int start)
{
	char	*content;
	char	*temp;

	content = ft_substr(tokenizer->input, start,
			tokenizer->position - start);
	if (!content)
	{
		free(result);
		return (NULL);
	}
	temp = ft_strjoin_free(result, content);
	free(content);
	return (temp);
}

static char	*process_quote_content(t_tokenizer *tokenizer,
		char quote, int start, char *result)
{
	while (tokenizer->input[tokenizer->position]
		&& tokenizer->input[tokenizer->position] != quote)
	{
		if (tokenizer->input[tokenizer->position] == '\\'
			&& tokenizer->input[tokenizer->position + 1] == quote)
		{
			result = handle_escaped_quote(tokenizer, quote, &start, result);
			if (!result)
				return (NULL);
		}
		else
			tokenizer->position++;
	}
	return (result);
}

char	*extract_quote_content(t_tokenizer *tokenizer,
		char quote, int start)
{
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	result = process_quote_content(tokenizer, quote, start, result);
	if (!result)
		return (NULL);
	if (start < tokenizer->position)
		return (handle_remaining_content(tokenizer, result, start));
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
