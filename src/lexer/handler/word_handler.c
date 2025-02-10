/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_handler.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:32:09 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/10 11:10:19 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int is_safe_char(const char *str, size_t pos)
{
	if (!str || pos == (size_t)-1)
		return (0);
	return (str[pos] != '\0');
}

/* Check word token termination conditions (meets null, operator, space) */
static int	should_stop_word(t_tokenizer *tokenizer)
{
	char	current;

	if (!tokenizer || !tokenizer->input)
		return (1);
	current = tokenizer->input[tokenizer->position];
	if (!current)
		return (1);
	if (is_in_quotes(tokenizer))
		return (0);
	return (is_operator(&tokenizer->input[tokenizer->position])
		|| ft_isspace(current));
}

/* Handles special characters and creates appropriate token type */
static t_token_type	get_word_token_type(char *word)
{
	if (!word || !*word)
		return (TOKEN_WORD);
	if (word[0] == '$')
		return (TOKEN_VAR);
	return (TOKEN_WORD);
}

/* Process word expansions and create appropriate token */
static t_token	*expand_word(t_tokenizer *tokenizer, char *word)
{
	char		*expanded;
	t_token		*token;

	if (!tokenizer || !word)
		return (NULL);
	if (tokenizer->in_quote)
	{
		token = create_token(word, get_word_token_type(word));
		if (!token)
			return (NULL);
		return (token);
	}
	expanded = handle_expansion(tokenizer, word);
	if (!expanded)
		return (free(word), (NULL));
	if (has_wildcard(expanded))
	{
		token = handle_wildcard_token(expanded);
		free(expanded);
		free(word);
		return (token);
	}
	token = create_token(expanded, get_word_token_type(expanded));
	if (!token)
		free(expanded);
	free(word);
	return (token);
}

/* Generate word tokens */
t_token	*handle_word(t_tokenizer *tokenizer)
{
	int		start;
	char	*content;

	if (!tokenizer || !tokenizer->input || !tokenizer->input[0])
		return (NULL);
	if (is_special_char(tokenizer->input[tokenizer->position])
		&& !is_quote(tokenizer->input[tokenizer->position]))
	{
		ft_putstr_fd("minishell: invalid character\n", STDERR_FILENO);
		return (NULL);
	}
	if (!validate_quotes(tokenizer->input + tokenizer->position))
		return (NULL);
	start = tokenizer->position;
	while (is_safe_char(tokenizer->input, tokenizer->position))
	{
		if (is_quote(tokenizer->input[tokenizer->position]))
		{
			handle_quote(tokenizer);
			if (tokenizer->position < 0)
				return (NULL);
		}
		else if (should_stop_word(tokenizer))
			break ;
		tokenizer->position++;
	}
	if (start >= tokenizer->position)
		return (NULL);
	content = ft_substr(tokenizer->input, start,
			tokenizer->position - start);
	if (!content)
		return (NULL);
	return (expand_word(tokenizer, content));
}
