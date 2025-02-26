/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 10:25:56 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/26 14:51:39 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*handle_quote_in_word(t_tokenizer *tokenizer, char *result,
						t_quote_type *current_quote_type)
{
	t_quoted_result	*quoted_result;
	char			*joined;

	quoted_result = extract_quoted_content(tokenizer,
			tokenizer->input[tokenizer->position]);
	if (!quoted_result)
		return (result);
	joined = join_words(result, quoted_result->content);
	*current_quote_type = quoted_result->quote_type;
	free(quoted_result);
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

t_quoted_result	*extract_quoted_content(t_tokenizer *tokenizer, char quote)
{
	int				start;
	int				len;
	t_quoted_result	*result;

	result = (t_quoted_result *)malloc(sizeof(t_quoted_result));
	if (!result)
		return (NULL);
	tokenizer->position++;
	start = tokenizer->position;
	while (tokenizer->input[tokenizer->position]
		&& tokenizer->input[tokenizer->position] != quote)
		tokenizer->position++;
	if (!tokenizer->input[tokenizer->position])
	{
		free(result);
		return (NULL);
	}
	len = tokenizer->position - start;
	result->content = ft_substr(tokenizer->input, start, len);
	if (quote == '\'')
		result->quote_type = QUOTE_SINGLE;
	else
		result->quote_type = QUOTE_DOUBLE;
	tokenizer->position++;
	return (result);
}
