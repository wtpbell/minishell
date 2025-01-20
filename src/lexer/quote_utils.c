/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:40:44 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/20 12:06:46 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static int get_token_len(char *str)
{
	int		len;
	char	quote;

	len = 0;
	while (str[len] && str[len] != ' ')
	{
		if (is_quote(str[len]))
		{
			quote = str[len++];
			while (str[len] && str[len] != quote)
				len++;
			if (str[len])
				len++;
		}
		else
			len++;
	}
	return (len);
}

static char	*extract_token(char *str, int len)
{
	char	*token;
	int		i;

	token = malloc(sizeof(char) * (len + 1));
	if (!token)
		return (NULL);
	i = 0;
	while(i < len)
	{
		token[i] = str[i];
		i++;
	}
	token[i] = '\0';
	return (token);
}

t_token *tokenize_with_quotes(char *input)
{
	t_token	*head;
	t_token	*current;
	int		i;
	int		len;

	i = 0;
	head = NULL;
	while(input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (!input[i])
			break ;
		len = get_token_len(input + i);
		if (!head)
		{
			head = create_token(extract_token(input + i, len), TOKEN_WORD);
			current = head;
		}
		else
		{
			current->next = create_token(extract_token(input + i, len), TOKEN_WORD);
			current = current->next;
		}
		i += len;
	}
	return (head);
}
