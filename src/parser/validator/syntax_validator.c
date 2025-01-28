/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   syntax_validator.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:31:13 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/28 15:37:48 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_syntax_error	validate_operator_precedence(t_ast_node *node)
{
	if (!node)
		return (SYNTAX_OK);
	if (node->type == TOKEN_PIPE)
	{
		if (!node->left || !node->right)
			return (SYNTAX_INVALID_COMBINATION);
	}
	if (node->type == TOKEN_AND || node->type == TOKEN_OR)
	{
		if (!node->left || !node->right)
			return (SYNTAX_INVALID_COMBINATION);
	}
	if (node->type == TOKEN_LPAREN || node->type == TOKEN_RPAREN)
	{
		if (!node->left || node->right)
			return (SYNTAX_INVALID_COMBINATION);
	}
	if (node->type == TOKEN_REDIR_IN || node->type == TOKEN_REDIR_OUT
		|| node->type == TOKEN_HEREDOC || node->type == TOKEN_APPEND)
	{
		if (!node->left || node->right != TOKEN_WORD)
			return (SYNTAX_INVALID_COMBINATION);
		if (!node->left && node->right != TOKEN_WORD
			&& node->left->type != TOKEN_REDIR_IN && node->left->type != TOKEN_REDIR_OUT
			&& node->left->type != TOKEN_HEREDOC && node->left->type != TOKEN_APPEND)
			return (SYNTAX_INVALID_COMBINATION);
	}
	if (node->type == TOKEN_PIPE)
	{
		if (node->right && node->right->type == TOKEN_PIPE)
			return (SYNTAX_INVALID_SEQUENCE);
	}
	if (node->type == TOKEN_AND || node->type == TOKEN_OR)
	{
		if (node->right && (node->right->type == TOKEN_AND
				|| node->right->type == TOKEN_OR))
			return (SYNTAX_INVALID_SEQUENCE);
	}
	if (node->type == TOKEN_LPAREN)
	{
		if (!node->left)
			return (SYNTAX_INVALID_SUBSHELL);
		if (node->left->type != TOKEN_WORD
			&& node->left->type != TOKEN_PIPE
			&& node->left->type != TOKEN_AND
			&& node->left->type != TOKEN_OR)
			return (SYNTAX_INVALID_SUBSHELL);
	}
	return (SYNTAX_OK);
}

t_syntax_error	validate_syntax_tree(t_ast_node *root)
{
	t_syntax_error	error;

	if (!root)
		return (SYNTAX_OK);
	error = validate_operator_precedence(root);
	if (error != SYNTAX_OK)
		return (error);
	error = validate_syntax_tree(root->left);
	if (error != SYNTAX_OK)
		return (error);
	error = validate_syntax_tree(root->right);
	if (error != SYNTAX_OK)
		return (error);
	return (SYNTAX_OK);
}
