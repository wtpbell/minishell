/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 10:23:45 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/13 09:57:43 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*join_words(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

int	is_wildcard_after_quote(t_tokenizer *tokenizer)
{
	return (tokenizer->input[tokenizer->position] == '*'
		&& tokenizer->position > 0
		&& (tokenizer->input[tokenizer->position - 1] == '\''
			|| tokenizer->input[tokenizer->position - 1] == '\"'));
}
