/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_handler.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:54:52 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/27 10:36:06 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	handle_command_args(t_ast_node *node, t_token **token)
{
	t_token	*current;

	if ((*token)->type == TOKEN_WORD || (*token)->type == TOKEN_WILDCARD)
	{
		add_arg_to_node(node, (*token)->content, (*token)->quote_type);
		*token = (*token)->next;
	}
	current = *token;
	while (current && (current->type == TOKEN_WORD
			|| current->type == TOKEN_WILDCARD))
	{
		add_arg_to_node(node, current->content, current->quote_type);
		current = current->next;
	}
	*token = current;
}

static int	handle_command_redirs(t_ast_node *node, t_token **token)
{
	t_token	*temp;

	if (*token && is_redirection(*token))
	{
		temp = *token;
		while (temp && is_redirection(temp))
		{
			if (!temp->next || temp->next->type != TOKEN_WORD
					|| !temp->next->content)
				return (0);
			add_redirection(node, temp->type, temp->next->content);
			temp = temp->next->next;
		}
		*token = temp;
	}
	return (1);
}

/* Parse command */
t_ast_node	*parse_command(t_token **token)
{
	t_ast_node	*node;
	t_token		*temp;

	if (!token || !*token)
		return (NULL);
	node = create_ast_node(TOKEN_WORD);
	if (!node)
		return (NULL);
	handle_command_args(node, token);
	if (!handle_command_redirs(node, token))
		return (free_ast(node), NULL);
	if (*token && ((*token)->type == TOKEN_WORD
			|| (*token)->type == TOKEN_WILDCARD))
	{
		temp = *token;
		while (temp && (temp->type == TOKEN_WORD
				|| temp->type == TOKEN_WILDCARD))
		{
			add_arg_to_node(node, temp->content, temp->quote_type);
			temp = temp->next;
		}
		*token = temp;
	}
	return (node);
}
