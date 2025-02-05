/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_handler.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:32:09 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/05 11:06:04 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Check word token termination conditions (meets null, operator, space) */
static int	should_stop_word(t_tokenizer *tokenizer)
{
	char	current;

	current = tokenizer->input[tokenizer->position];
	if (!current)
		return (1);
	if (!is_in_quotes(tokenizer)
		&& (is_operator(&tokenizer->input[tokenizer->position])
			|| ft_isspace(tokenizer->input[tokenizer->position])))
		return (1);
	return (0);
}

static t_token	*add_wildcard_token(t_token **first,
								t_token **current,
								char *word)
{
	t_token	*new_token;

	new_token = create_token(word, TOKEN_WORD);
	if (!*first)
	{
		*first = new_token;
		*current = new_token;
	}
	else
	{
		(*current)->next = new_token;
		*current = new_token;
	}
	return (new_token);
}

static t_token	*create_wildcard_tokens(char *pattern)
{
	char	**matches;
	t_token	*first;
	t_token	*current;
	int		i;

	matches = expand_wildcards(pattern);
	if (!matches)
		return (create_token(pattern, TOKEN_WORD));
	first = NULL;
	current = NULL;
	i = 0;
	while (matches[i])
	{
		if (!add_wildcard_token(&first, &current, matches[i]))
		{
			ft_free_strarr(matches);
			free_tokens(first);
			return (NULL);
		}
	}
	ft_free_strarr(matches);
	return (first);
}

static t_token	*expand_word(t_tokenizer *tokenizer, char *word)
{
	char		*expanded;
	t_token		*token;

	if (!tokenizer->in_quote)
	{
		expanded = handle_expansion(tokenizer, word);
		if (!expanded)
		{
			free(word);
			return (NULL);
		}
		if (has_wildcard(expanded))
		{
			token = handle_wildcard_token(expanded);
			free(expanded);
			free(word);
			return (token);
		}
		free(word);
		return (create_token(expanded, get_word_token_type(expanded)));
	}
	token = create_token(word, get_word_token_type(word));
	if (!token)
		free(word);
	return (token);
}

/*
** Generate word tokens
** Extract strings, handling quotes and extensions
*/
t_token	*handle_word(t_tokenizer *tokenizer)
{
	int		start;
	char	*content;

	if (!validate_quotes(tokenizer->input + tokenizer->position))
		return (NULL);
	start = tokenizer->position;
	while (tokenizer->input[tokenizer->position])
	{
		if (is_quote(tokenizer->input[tokenizer->position]))
			handle_quote(tokenizer);
		else if (should_stop_word(tokenizer))
			break ;
		tokenizer->position++;
	}
	content = ft_substr(tokenizer->input, start,
			tokenizer->position - start);
	if (!content)
		return (NULL);
	return (expand_word(tokenizer, content));
}
