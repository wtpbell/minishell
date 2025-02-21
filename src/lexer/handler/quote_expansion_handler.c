/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_expansion_handler.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 15:24:00 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/21 11:10:24 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	is_escaped_var(const char *str)
{
	if (!str || !*str)
		return (0);
	return (str[0] == '\\' && str[1] == '$');
}

static char	*handle_double_quote_expansion(t_tokenizer *tokenizer,
										char *result)
{
	char	*expanded;

	if (!result || !tokenizer)
		return (NULL);
	if (is_escaped_var(result))
	{
		if (result[2] == '?' && result[3] == '\0')
			return (ft_strdup("$?"));
		return (result);
	}
	if (ft_strncmp(result, "$?", 2) == 0)
		return (free(result), expand_exit_status());
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
