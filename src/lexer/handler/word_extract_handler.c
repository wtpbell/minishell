/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_extract_handler.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/21 09:46:58 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/21 12:56:43 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*get_next_word_part(t_tokenizer *tokenizer)
{
	char	*part;
	char	quote;

	if (is_quote(tokenizer->input[tokenizer->position]))
	{
		quote = tokenizer->input[tokenizer->position];
		if (!tokenizer->in_quote)
		{
			tokenizer->quote_char = quote;
			tokenizer->in_quote = 1;
		}
		else if (tokenizer->quote_char == quote)
		{
			tokenizer->in_quote = 0;
			tokenizer->quote_char = 0;
		}
		part = extract_quoted_content_with_expansion(tokenizer, quote);
	}
	else
	{
		part = ft_substr(tokenizer->input, tokenizer->position, 1);
		tokenizer->position++;
	}
	return (part);
}

static char	*handle_exit_status_in_word(t_tokenizer *tokenizer)
{
	char	*part;

	part = expand_exit_status();
	tokenizer->position += 2;
	return (part);
}

static char	*join_and_check(char *result, char *temp)
{
	char	*joined;

	joined = join_words(result, temp);
	if (!joined)
		return (NULL);
	return (joined);
}

char	*extract_word(t_tokenizer *tokenizer)
{
	char	*result;
	char	*temp;
	char	*joined;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (tokenizer->input[tokenizer->position]
		&& !ft_isspace(tokenizer->input[tokenizer->position])
		&& !is_operator(&tokenizer->input[tokenizer->position]))
	{
		if (is_exit_status_var(&tokenizer->input[tokenizer->position])
			&& !tokenizer->in_quote)
			temp = handle_exit_status_in_word(tokenizer);
		else
			temp = get_next_word_part(tokenizer);
		if (!temp)
			return (free(result), NULL);
		joined = join_and_check(result, temp);
		if (!joined)
			return (free(result), NULL);
		result = joined;
	}
	return (result);
}
