/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_extract_handler.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 12:04:25 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/14 09:05:47 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*handle_char_in_word(t_tokenizer *tokenizer, char *result)
{
	char	*temp;
	char	*joined;

	temp = ft_substr(tokenizer->input, tokenizer->position, 1);
	if (!temp)
		return (result);
	joined = ft_strjoin(result, temp);
	free(result);
	free(temp);
	tokenizer->position++;
	return (joined);
}

t_quoted_result	*extract_quoted_content(t_tokenizer *tokenizer, char quote,
			t_quote_type current_quote_type)
{
	int				start;
	int				len;
	t_quoted_result	*result;

	result = ft_calloc(1, sizeof(t_quoted_result));
	if (!result)
		return (NULL);
	tokenizer->position++;
	start = tokenizer->position;
	while (tokenizer->input[tokenizer->position]
		&& tokenizer->input[tokenizer->position] != quote)
		tokenizer->position++;
	if (!tokenizer->input[tokenizer->position])
		return (free(result), NULL);
	len = tokenizer->position - start;
	result->content = ft_substr(tokenizer->input, start, len);
	if (current_quote_type == QUOTE_DOUBLE && quote == '\'')
		result->quote_type = QUOTE_DOUBLE;
	else
		result->quote_type = quote_type_select(current_quote_type, quote);
	tokenizer->position++;
	if (tokenizer->input[tokenizer->position] == '*')
		result->quote_type = QUOTE_MIXED;
	return (result);
}
