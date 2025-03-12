// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   quote_utils.c                                      :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: spyun <spyun@student.codam.nl>               +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2025/02/18 10:25:56 by spyun         #+#    #+#                 */
// /*   Updated: 2025/03/12 11:37:35 by spyun         ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

#include "lexer.h"

char	*handle_quote_in_word(t_tokenizer *tokenizer, char *result,
			t_quote_type *current_quote_type)
{
	t_quoted_result	*quoted_result;
	char			quote_char;
	char			quote_str[2];
	char			*temp_result;
	char			*quoted_content;
	char			*quoted_end;

	quote_char = tokenizer->input[tokenizer->position];
	quote_str[0] = quote_char;
	quote_str[1] = '\0';
	quoted_result = extract_quoted_content(tokenizer, quote_char, *current_quote_type);
	if (!quoted_result)
		return (result);
	quoted_content = ft_strjoin(quote_str, quoted_result->content);
	quoted_end = ft_strjoin(quoted_content, quote_str);
	temp_result = ft_strjoin(result, quoted_end);
	*current_quote_type = quoted_result->quote_type;
	free(result);
	free(quoted_content);
	free(quoted_end);
	free(quoted_result->content);
	free(quoted_result);
	return (temp_result);
}

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

	result = (t_quoted_result *)ft_calloc(1, sizeof(t_quoted_result));
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
	if (current_quote_type == QUOTE_NONE)
		result->quote_type = quote == '\'' ? QUOTE_SINGLE : QUOTE_DOUBLE;
	else if (current_quote_type == QUOTE_SINGLE && quote == '\'')
		result->quote_type = QUOTE_NONE;
	else if (current_quote_type == QUOTE_DOUBLE && quote == '\"')
		result->quote_type = QUOTE_NONE;
	else
		result->quote_type = QUOTE_MIXED;
	tokenizer->position++;
	return (result);
}
