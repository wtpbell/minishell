/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:55:35 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/13 10:42:47 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*create_subshell_node(void)
{
	t_ast_node	*node;

	node = create_ast_node(TOKEN_SUBSHELL);
	if (!node)
		return (NULL);
	node->is_subshell = 1;
	return (node);
}

static t_ast_node	*parse_group_content(t_token **token)
{
	t_ast_node	*content;
	t_ast_node	*subshell_node;

	subshell_node = create_subshell_node();
	if (!subshell_node)
		return (NULL);
	*token = (*token)->next;
	content = parse_command_sequence(token, TOKEN_RPAREN);
	if (!content)
	{
		free_ast(subshell_node);
		return (handle_group_error("invalid subshell syntax"));
	}
	subshell_node->left = content;
	return (subshell_node);
}

static t_ast_node	*handle_group_closure(t_token **token, t_ast_node *node)
{
	t_ast_node	*result;

	if (!*token || (*token)->type != TOKEN_RPAREN)
	{
		free_ast(node);
		return (handle_group_error("missing closing parenthesis"));
	}
	*token = (*token)->next;
	if (*token && is_logic_operator(*token))
	{
		result = handle_logic_operation(token, node);
		if (!result)
			return (free_ast(node), NULL);
		return (result);
	}
	else if (*token && (*token)->type == TOKEN_PIPE)
	{
		result = handle_pipe_right(token, node);
		if (!result)
			return (free_ast(node), NULL);
		return (result);
	}
	return (node);
}

t_ast_node	*parse_group(t_token **token)
{
	t_ast_node	*node;

	if (!token || !*token)
		return (NULL);
	if ((*token)->type != TOKEN_LPAREN)
		return (parse_command_sequence(token, TOKEN_EOF));
	node = parse_group_content(token);
	if (!node)
		return (NULL);
	return (handle_group_closure(token, node));
}
