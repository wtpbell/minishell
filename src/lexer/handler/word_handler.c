/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_handler.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:32:09 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/14 09:25:33 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	skip_spaces(t_tokenizer *tokenizer)
{
	while (tokenizer->input[tokenizer->position]
		&& ft_isspace(tokenizer->input[tokenizer->position]))
		tokenizer->position++;
}

static char	*process_word_character(t_tokenizer *tokenizer, char *result,
				t_quote_type *quote_type, int *quote_ended)
{
	if (is_quote(tokenizer->input[tokenizer->position]))
	{
		result = handle_quote_in_word(tokenizer, result, quote_type);
		*quote_ended = 1;
	}
	else
	{
		if (*quote_ended && tokenizer->input[tokenizer->position] == '*')
			*quote_type = QUOTE_MIXED;
		result = handle_char_in_word(tokenizer, result);
		*quote_ended = 0;
	}
	return (result);
}

static char	*extract_word(t_tokenizer *tokenizer, t_quote_type *quote_type)
{
	char	*result;
	int		quote_ended;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	quote_ended = 0;
	while (tokenizer->input[tokenizer->position]
		&& !ft_isspace(tokenizer->input[tokenizer->position])
		&& !is_operator(&tokenizer->input[tokenizer->position]))
	{
		result = process_word_character(tokenizer,
				result, quote_type, &quote_ended);
		if (!result)
			return (NULL);
	}
	return (result);
}

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

t_token	*handle_word(t_tokenizer *tokenizer)
{
	char			*content;
	t_token			*token;
	t_quote_type	quote_type;

	quote_type = QUOTE_NONE;
	if (!tokenizer || !tokenizer->input)
		return (NULL);
	skip_spaces(tokenizer);
	content = extract_word(tokenizer, &quote_type);
	if (!content)
		return (NULL);
	token = analyze_and_create_token(content);
	if (token)
		token->quote_type = quote_type;
	return (token);
}
