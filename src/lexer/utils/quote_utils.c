/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 10:25:56 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/18 10:26:02 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*handle_quote_in_word(t_tokenizer *tokenizer, char *result)
{
	char	*quoted;
	char	*joined;

	quoted = extract_quoted_content(tokenizer,
			tokenizer->input[tokenizer->position]);
	if (!quoted)
		return (result);
	joined = join_words(result, quoted);
	return (joined);
}

char	*handle_char_in_word(t_tokenizer *tokenizer, char *result)
{
	char	*temp;
	char	*joined;

	temp = ft_substr(tokenizer->input, tokenizer->position, 1);
	if (!temp)
		return (result);
	joined = join_words(result, temp);
	tokenizer->position++;
	return (joined);
}

char	*extract_quoted_content(t_tokenizer *tokenizer, char quote)
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
