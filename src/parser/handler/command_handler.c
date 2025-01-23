/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_handler.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:54:52 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/23 19:46:09 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* check for instruction tokens */
static int	is_command_token(t_token *token)
{
	return (token && token->type == TOKEN_WORD);
}

/* create and initialise a single instruction node */
static t_ast_node	*create_command_node(t_token **token)
{
	t_ast_node	*node;

	if (!is_command_token(*token))
		return (NULL);
	node = create_ast_node(TOKEN_WORD);
	if (!node)
		return (NULL);
	add_arg_to_node(node, (*token)->content);
	*token = (*token)->next;
	return (node);
}
/*  Parse the token to create an AST node consisting of commands and arguments */
t_ast_node	*parse_command(t_token **token)
{
	t_ast_node	*node;

	if (!token || !*token)
		return (NULL);
	node = create_command_node(token);
	if (!node)
		return (NULL);
	while (*token && is_command_token(*token))
	{
		add_arg_to_node(node, (*token)->content);
		*token = (*token)->next;
	}
	return (node);
}
