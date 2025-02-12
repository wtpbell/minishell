/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   operator_handler.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:34:05 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/03 09:51:20 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* check if string is a valid operator */
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

/* Converting operators to tokens */
t_token	*handle_operator(t_tokenizer *tokenizer)
{
	t_token_type	type;
	char			*content;
	int				len;
	char			*input;

	input = tokenizer->input + tokenizer->position;
	// printf("print input %s\n", input);
	if (!validate_operator(input))
		return (NULL);
	type = get_operator_type(input);
	// printf("print type %u\n", type);
	if (type == TOKEN_WORD)
		return (NULL);
	len = get_operator_len(type);
	content = ft_substr(input, 0, len);
	if (!content)
		return (NULL);
	tokenizer->position += len;
	return (create_token(content, type));
}
