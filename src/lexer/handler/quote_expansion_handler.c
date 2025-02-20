/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_expansion_handler.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 15:24:00 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/20 10:27:24 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*handle_double_quote_expansion(t_tokenizer *tokenizer,
	char *result)
{
	char	*expanded;

	if (!result || !tokenizer)
		return (NULL);
	if (ft_strncmp(result, "$?", 2) == 0)
	{
		free(result);
		return (ft_itoa(g_exit_status));
	}
	if (ft_strchr(result, '$'))
	{
		expanded = handle_expansion(tokenizer, result);
		free(result);
		return (expanded);
	}
	return (result);
}

char	*extract_quoted_content_with_expansion(t_tokenizer *tokenizer,
	char quote)
{
	int		start;
	char	*result;

	tokenizer->position++;
	start = tokenizer->position;
	result = extract_quote_content(tokenizer, quote, start);
	tokenizer->position++;
	if (quote == '"')
		result = handle_double_quote_expansion(tokenizer, result);
	return (result);
}

