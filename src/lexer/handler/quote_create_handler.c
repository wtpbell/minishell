/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_create_handler.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 12:02:43 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/12 12:24:01 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_quote_type	quote_type_select(t_quote_type current_type, char quote)
{
	if (current_type == QUOTE_NONE)
	{
		if (quote == '\'')
			return (QUOTE_SINGLE);
		return (QUOTE_DOUBLE);
	}
	if (current_type == QUOTE_SINGLE && quote == '\'')
		return (QUOTE_NONE);
	if (current_type == QUOTE_DOUBLE && quote == '\"')
		return (QUOTE_NONE);
	return (QUOTE_MIXED);
}

static void	free_quoted_result(t_quoted_result *quoted_result)
{
	if (quoted_result)
	{
		free(quoted_result->content);
		free(quoted_result);
	}
}

static char	*handle_quote_error(char *result, t_quoted_result *quoted_result)
{
	free(result);
	free_quoted_result(quoted_result);
	return (NULL);
}


static char	*create_full_quoted_str(t_quoted_result *quoted_result)
{
	if (quoted_result->content == NULL)
		return (ft_strdup(""));
	return (ft_strdup(quoted_result->content));
}

char	*handle_quote_in_word(t_tokenizer *tokenizer, char *result,
			t_quote_type *current_quote_type)
{
	char			quote_str[2];
	char			*temp_result;
	char			*temp_str;
	t_quoted_result	*quoted_result;

	quote_str[0] = tokenizer->input[tokenizer->position];
	quote_str[1] = '\0';
	quoted_result = extract_quoted_content(tokenizer, quote_str[0],
			*current_quote_type);
	if (!quoted_result)
		return (result);
	temp_str = create_full_quoted_str(quoted_result);
	if (!temp_str)
		return (handle_quote_error(result, quoted_result));
	temp_result = ft_strjoin(result, temp_str);
	free(temp_str);
	if (!temp_result)
		return (handle_quote_error(result, quoted_result));
	*current_quote_type = quoted_result->quote_type;
	free(result);
	free_quoted_result(quoted_result);
	return (temp_result);
}
