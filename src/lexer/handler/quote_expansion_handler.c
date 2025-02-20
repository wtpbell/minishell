/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_expansion_handler.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 15:24:00 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/20 08:40:34 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char *handle_double_quote_expansion(t_tokenizer *tokenizer, char *result)
{
    char    *expanded;
    char    *temp;
    int     i;
    int     j;

    temp = ft_strdup("");
    i = 0;
    while (result[i])
    {
        if (result[i] == '\\' && result[i + 1] == '$')
        {
            temp = ft_strjoin_char(temp, '$');
            i += 2;
        }
        else
            temp = ft_strjoin_char(temp, result[i++]);
    }
    free(result);
    result = temp;

    if (ft_strcmp(result, "$?") == 0)
    {
        free(result);
        result = ft_itoa(g_exit_status);
    }
    else if (ft_strchr(result, '$'))
    {
        expanded = handle_expansion(tokenizer, result);
        free(result);
        result = expanded;
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

