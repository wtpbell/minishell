/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:30:39 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/20 10:38:49 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*create_token(char *content, t_token_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = content;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

static t_token_type	get_token_type(char *str)
{
	if (!str)
		return (TOKEN_WORD);
	if (str[0] == '|' && !str[1])
		return (TOKEN_PIPE);
	if (str[0] == '<')
	{
		if (str[1] == '<' && str[1])
			return (TOKEN_HEREDOC);
		return (TOKEN_REDIR_IN);
	}
	if (str[0] == '>')
	{
		if (str[1] == '>' && str[1])
			return (TOKEN_APPEND);
		return (TOKEN_REDIR_OUT);
	}
	return (TOKEN_WORD);
}

t_token	**tokenize_input(char *input)
{
	t_token	**head;
	t_token	*current;
	char	**tokens;
	int		i;

	if (!input)
		return (NULL);
	tokens = ft_split(input, ' ');
	if (!tokens)
		return (NULL);
	head = NULL;
	while (tokens[i])
	{
		if (!head)
		{
			head = create_token(tokens[i], get_token_type(tokens[i]));
			current = head;
		}
		else
		{
			current->next = create_token(tokens[i], get_token_type(tokens[i]));
			current = current->next;
		}
		i++;
	}
	free(tokens);
	return (head);
}
