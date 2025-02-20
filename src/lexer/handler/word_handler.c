/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_handler.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:32:09 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/20 11:21:54 by spyun         ########   odam.nl         */
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

static int	has_unescaped_var(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (i == 0 || str[i - 1] != '\\'))
			return (1);
		i++;
	}
	return (0);
}

/* Extract word */
static char	*extract_word(t_tokenizer *tokenizer)
{
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (tokenizer->input[tokenizer->position]
		&& !ft_isspace(tokenizer->input[tokenizer->position])
		&& !is_operator(&tokenizer->input[tokenizer->position]))
	{
		if (is_quote(tokenizer->input[tokenizer->position]))
			result = handle_quote_in_word(tokenizer, result);
		else
			result = handle_char_in_word(tokenizer, result);
		if (!result)
			return (NULL);
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
	char	*temp;
	char	*quoted;

	if (!tokenizer || !tokenizer->input)
		return (NULL);
	skip_spaces(tokenizer);
	if (is_quote(tokenizer->input[tokenizer->position]))
	{
		content = ft_strdup("");
		while (is_quote(tokenizer->input[tokenizer->position]))
		{
			quoted = extract_quoted_content_with_expansion(tokenizer,
					tokenizer->input[tokenizer->position]);
			if (!quoted)
				return (free(content), NULL);
			temp = join_words(content, quoted);
			content = temp;
		}
	}
	else
		content = extract_word(tokenizer);
	if (!content)
		return (NULL);
	if (has_unescaped_var(content))
	{
		temp = handle_expansion(tokenizer, content);
		free(content);
		content = temp;
	}
	return (analyze_and_create_token(content));
}
