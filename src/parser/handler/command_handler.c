/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_handler.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:54:52 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/11 14:53:14 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


/* Parse command */
t_ast_node	*parse_command(t_token **token)
{
	t_ast_node	*node;
	t_token		*current;

	if (!token || !*token)
		return (NULL);
	node = create_ast_node(TOKEN_WORD);
	if (!node)
		return (NULL);
	if ((*token)->type == TOKEN_WORD)
	{
		add_arg_to_node(node, (*token)->content);
		*token = (*token)->next;
	}
	current = *token;
	while (current && current->type == TOKEN_WORD)
	{
		add_arg_to_node(node, current->content);
		current = current->next;
	}
	*token = current;
	if (*token && is_redirection(*token))
	{
		t_token *temp = *token;
		while (temp && is_redirection(temp))
		{
			if (!temp->next || temp->next->type != TOKEN_WORD)
				return (free_ast(node), NULL);
			add_redirection(node, temp->type, temp->next->content);
			temp = temp->next->next;
		}
		*token = temp;
	}
	return (node);
}
