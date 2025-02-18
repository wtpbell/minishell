/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 10:25:56 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/18 11:28:40 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Check for characters that require special handling within double quotes */
int	is_special_in_quotes(char c, char quote_char)
{
	if (quote_char == '"')
		return (c == '$' || c == '`' || c == '\\');
	return (0);
}

/* Check if you are currently inside quotes */
int	is_in_quotes(t_tokenizer *tokenizer)
{
	return (tokenizer->in_quote);
}

/* Get the current quote state */
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

/* Handle characters inside a word */
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

/* Extract content inside quotes */
char	*extract_quoted_content(t_tokenizer *tokenizer, char quote)
{
	int		start;
	char	*content;
	char	*result;
	int		i;

	tokenizer->position++;
	start = tokenizer->position;
	result = ft_strdup("");
	while (tokenizer->input[tokenizer->position]
		&& tokenizer->input[tokenizer->position] != quote)
	{
		if (tokenizer->input[tokenizer->position] == '\\'
			&& tokenizer->input[tokenizer->position + 1] == quote)
		{
			content = ft_substr(tokenizer->input, start,
				tokenizer->position - start);
			result = ft_strjoin_free(result, content);
			result = ft_strjoin_char(result, quote);
			tokenizer->position += 2;
			start = tokenizer->position;
		}
		else
			tokenizer->position++;
	}
	if (start < tokenizer->position)
	{
		content = ft_substr(tokenizer->input, start,
			tokenizer->position - start);
		result = ft_strjoin_free(result, content);
	}
	tokenizer->position++;
	return (result);
}
