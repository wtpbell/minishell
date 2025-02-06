/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:55:35 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/06 16:34:41 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Create a subshell node */
t_ast_node	*create_subshell_node(void)
{
	t_ast_node	*node;

	node = create_ast_node(TOKEN_SUBSHELL);
	if (!node)
		return (NULL);
	node->is_subshell = 1;
	return (node);
}

/* Combine a subshell with a redirection */
static t_ast_node	*combine_subshell_redirection(t_ast_node *subshell, t_token **token)
{
	t_ast_node	*redir_node;

	if (!token || !*token || !is_redirection(*token))
		return (subshell);
	redir_node = create_redirection_node(token);
	if (!redir_node)
	{
		free_ast(subshell);
		return (NULL);
	}
	redir_node->left = subshell;
	if (*token && is_redirection(*token))
		return (combine_subshell_redirection(redir_node, token));
	return (redir_node);
}

/* Parse group */
t_ast_node	*parse_group(t_token **token)
{
	t_ast_node	*node;
	t_ast_node	*subshell_node;

	if (!token || !*token)
		return (NULL);
	if (!is_left_paren(*token))
		return (parse_logic(token));
	*token = (*token)->next;
	subshell_node = create_subshell_node();
	if (!subshell_node)
		return (NULL);
	node = parse_logic(token);
	if (!node || !*token || !is_right_paren(*token))
	{
		free_ast(subshell_node);
		return (handle_group_error("invalid subshell syntax"));
	}
	subshell_node->left = node;
	*token = (*token)->next;
	if (*token && !is_valid_after_subshell(*token))
	{
		free_ast(subshell_node);
		return (handle_group_error("invalid token after subshell"));
	}
	if (*token && is_redirection(*token))
		return (combine_subshell_redirection(subshell_node, token));
	return (subshell_node);
}
