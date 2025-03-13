/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operator_handler.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:34:05 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/13 09:36:12 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	validate_operator(char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '|' && *(str + 1) == '|')
		return (1);
	if (*str == '&' && *(str + 1) == '&')
		return (1);
	if (*str == '<' && *(str + 1) == '<')
		return (1);
	if (*str == '>' && *(str + 1) == '>')
		return (1);
	if (*str == '|' || *str == '<' || *str == '>'
		|| *str == '(' || *str == ')')
		return (1);
	return (0);
}

t_token	*handle_operator(t_tokenizer *tokenizer)
{
	t_token_type	type;
	char			*content;
	int				len;
	char			*input;

	input = tokenizer->input + tokenizer->position;
	if (!validate_operator(input))
		return (NULL);
	type = get_operator_type(input);
	if (type == TOKEN_WORD)
		return (NULL);
	len = get_operator_len(type);
	content = ft_substr(input, 0, len);
	if (!content)
		return (NULL);
	tokenizer->position += len;
	return (create_token(content, type));
}
