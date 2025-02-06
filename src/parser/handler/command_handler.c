/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_handler.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:54:52 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/06 13:22:25 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* check for instruction tokens */
static int	is_command_token(t_token *token)
{
	if (!token)
		return (0);
	if (!token->content)
		return (0);
	if (token->type != TOKEN_WORD
		&& token->type != TOKEN_VAR
		&& token->type != TOKEN_WILDCARD)
		return (0);
	return (1);
}

/* create and initialise a single instruction node */

static t_ast_node	*create_command_node(t_token **token)
{
	t_ast_node	*node;
	t_token		*current;

	if (!token || !*token)
		return (NULL);
	current = *token;
	if (!is_command_token(current))
		return (NULL);
	node = create_ast_node(current->type);
	if (!node)
		return (NULL);
	if (current->content)
		add_arg_to_node(node, current->content);
	else
	{
		free_ast(node);
		return (NULL);
	}
	*token = current->next;
	return (node);
}

static int	process_command_args(t_ast_node *node, t_token **current)
{
	add_arg_to_node(node, (*current)->content);
	if (!node->args)
		return (0);
	if (!(*current)->next)
	{
		*current = NULL;
		return (0);
	}
	*current = (*current)->next;
	return (1);
}

t_ast_node	*parse_command(t_token **token)
{
	t_ast_node	*node;
	t_token		*current;

	if (!token || !*token)
		return (NULL);
	node = create_command_node(token);
	if (!node)
		return (NULL);
	current = *token;
	while (current && is_command_token(current))
	{
		if (!current->content)
			break ;
		if (!process_command_args(node, &current))
			break ;
	}
	*token = current;
	return (node);
}
