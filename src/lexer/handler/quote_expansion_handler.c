/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_expansion_handler.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 15:24:00 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/20 09:21:10 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*remove_backslash(char *str)
{
	int		i;
	int		j;
	char	*result;

	if (!str || !ft_strchr(str, '\\'))
		return (str);
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1])
			i++;
		result[j++] = str[i++];
	}
	result[j] = '\0';
	free(str);
	return (result);
}

static char	*handle_double_quote_expansion(t_tokenizer *tokenizer,
	char *result)
{
	char	*expanded;

	if (!result || !tokenizer)
		return (NULL);
	if (ft_strchr(result, '\\'))
	{
		if (ft_strncmp(result, "\\$?", 3) == 0)
			return (free(result), ft_strdup("$?"));
		result = remove_backslash(result);
		if (!result)
			return (NULL);
		return (result);
	}
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

