/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_handler.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:32:09 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/21 09:40:12 by spyun         ########   odam.nl         */
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

/* Expand exit status */
static char	*get_next_word_part(t_tokenizer *tokenizer)
{
	char	*part;

	if (is_quote(tokenizer->input[tokenizer->position]))
	{
		part = extract_quoted_content_with_expansion(tokenizer,
				tokenizer->input[tokenizer->position]);
	}
	else
	{
		part = ft_substr(tokenizer->input, tokenizer->position, 1);
		tokenizer->position++;
	}
	return (part);
}

/* Extract word */
static char	*extract_word(t_tokenizer *tokenizer)
{
	char	*result;
	char	*part;
	char	*temp;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (tokenizer->input[tokenizer->position]
		&& !ft_isspace(tokenizer->input[tokenizer->position])
		&& !is_operator(&tokenizer->input[tokenizer->position]))
	{
		if (is_exit_status_var(&tokenizer->input[tokenizer->position])
			&& !tokenizer->in_quote)
		{
			part = expand_exit_status();
			tokenizer->position += 2;
		}
		else
			part = get_next_word_part(tokenizer);
		if (!part)
			return (free(result), NULL);
		temp = join_words(result, part);
		if (!temp)
			return (free(result), NULL);
		result = temp;
	}
	return (result);
}

/* Analyze and create token */
static t_token	*analyze_and_create_token(char *content)
{
	t_token	*token;

	if (has_wildcard(content))
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
	return (analyze_and_create_token(content));
}
