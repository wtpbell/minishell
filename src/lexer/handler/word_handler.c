/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_handler.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:32:09 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/23 11:23:20 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	should_stop_word(t_tokenizer *tokenizer)
{
	char	current;

	current = tokenizer->input[tokenizer->position];
	if (!current)
		return (1);
	if (!is_in_quotes(tokenizer)
		&& (is_operator(&tokenizer->input[tokenizer->position])
			|| is_space(tokenizer->input[tokenizer->position])))
		return (1);
	return (0);
}

static char	*get_word_content(t_tokenizer *tokenizer, int start)
{
	char	*content;
	char	*expanded;

	content = ft_substr(tokenizer->input, start,
			tokenizer->position - start);
	if (!content)
		return (NULL);
	if (!tokenizer->in_quote || tokenizer->quote_char != '\'')
	{
		expanded = handle_expansion(content);
		free(content);
		return (expanded);
	}
	return (content);
}

t_token	*handle_word(t_tokenizer *tokenizer)
{
	int		start;
	char	*content;

	start = tokenizer->position;
	while (tokenizer->input[tokenizer->position])
	{
		if (is_quote(tokenizer->input[tokenizer->position]))
			handle_quote(tokenizer);
		else if (should_stop_word(tokenizer))
			break ;
		tokenizer->position++;
	}
	content = get_word_content(tokenizer, start);
	if (!content)
		return (NULL);
	return (create_token(content, TOKEN_WORD));
}
