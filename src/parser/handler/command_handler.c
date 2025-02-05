/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_handler.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:54:52 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/05 16:10:36 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* check for instruction tokens */
static int	is_command_token(t_token *token)
{
	if (!token)
		return (0);
	return (token && (token->type == TOKEN_WORD
			|| token->type == TOKEN_VAR
			|| token->type == TOKEN_WILDCARD));
}

/* create and initialise a single instruction node */
static t_ast_node	*create_command_node(t_token **token)
{
	t_ast_node	*node;

	if (!token || !*token )
		return (NULL);
	if (!is_command_token(*token))
		return (NULL);
	node = create_ast_node((*token)->type);
	if (!node)
		return (NULL);
	add_arg_to_node(node, (*token)->content);
	if ((*token)->next)
		*token = (*token)->next;
	return (node);
}

/* Parse the token to create an AST node consisting of commands and arguments */
t_ast_node	*parse_command(t_token **token)
{
	t_ast_node	*node;
    t_token		*current;

	if (!token || !*token )
		return (NULL);
	node = create_command_node(token);
	if (!node)
		return (NULL);
	current = *token;
	if (current->content)
	{
		add_arg_to_node(node, current->content);
		if (!node->args)
		{
			free_ast(node);
			return (NULL);
		}
	}
	if (current->next)
		current = current->next;
	while (current && is_command_token(current))
	{
		if (current->content)
		{
			add_arg_to_node(node, current->content);
			if (!node->args)
			{
				free_ast(node);
				return (NULL);
			}
		}
		if (!current->next)
			break ;
		current = current->next;
	}
	*token = current;
	return (node);
}
