/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_create.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 13:12:53 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/11 13:59:00 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Create a new token */
t_token	*create_token(char *content, t_token_type type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token) + 8);
	if (!token)
	{
		free(content);
		return (NULL);
	}
	ft_memset(token, 0, sizeof(t_token) + 8);
	token->type = type;
	token->content = content;
	token->next = NULL;
	return (token);
}

/* Add a new token to the token list */
void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!head || !new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}
