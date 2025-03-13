/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_validator.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:31:13 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/13 09:39:17 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_syntax_error	validate_pipe_syntax(t_ast_node *node)
{
	if (!node->left || !node->right)
		return (SYNTAX_INVALID_COMBINATION);
	return (SYNTAX_OK);
}

static t_syntax_error	validate_logic_syntax(t_ast_node *node)
{
	if (!node->left || !node->right)
		return (SYNTAX_INVALID_COMBINATION);
	if (node->right && (node->right->type == TOKEN_AND
			|| node->right->type == TOKEN_OR))
		return (SYNTAX_INVALID_SEQUENCE);
	return (SYNTAX_OK);
}

static t_syntax_error	validate_paren_syntax(t_ast_node *node)
{
	t_ast_node	*content;

	if (!node->left)
		return (SYNTAX_INVALID_SUBSHELL);
	if (node->right)
		return (SYNTAX_INVALID_SUBSHELL);
	if (node->type == TOKEN_LPAREN)
	{
		if (!node->left)
			return (SYNTAX_INVALID_SUBSHELL);
		content = node->left;
		if (content->type == TOKEN_PIPE
			&& (!content->left || !content->right))
			return (SYNTAX_INVALID_SUBSHELL);
		if (content->type == TOKEN_LPAREN)
			return (SYNTAX_INVALID_SUBSHELL);
	}
	return (SYNTAX_OK);
}

static t_syntax_error	validate_operator_precedence(t_ast_node *node)
{
	if (!node)
		return (SYNTAX_OK);
	if (node->type == TOKEN_PIPE)
		return (validate_pipe_syntax(node));
	if (node->type == TOKEN_AND || node->type == TOKEN_OR)
		return (validate_logic_syntax(node));
	if (node->type == TOKEN_LPAREN || node->type == TOKEN_RPAREN)
		return (validate_paren_syntax(node));
	if (node->type == TOKEN_REDIR_IN || node->type == TOKEN_REDIR_OUT
		|| node->type == TOKEN_HEREDOC || node->type == TOKEN_APPEND)
		return (validate_redir_syntax(node));
	return (SYNTAX_OK);
}

t_syntax_error	validate_syntax_tree(t_ast_node *root)
{
	t_syntax_error	left_error;
	t_syntax_error	right_error;
	t_syntax_error	node_error;

	if (!root)
		return (SYNTAX_OK);
	if (root->type == TOKEN_SUBSHELL)
	{
		node_error = validate_subshell_syntax(root);
		if (node_error != SYNTAX_OK)
			return (node_error);
	}
	else
	{
		node_error = validate_operator_precedence(root);
		if (node_error != SYNTAX_OK)
			return (node_error);
	}
	left_error = validate_syntax_tree(root->left);
	if (left_error != SYNTAX_OK)
		return (left_error);
	right_error = validate_syntax_tree(root->right);
	if (right_error != SYNTAX_OK)
		return (right_error);
	return (SYNTAX_OK);
}
