/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_validator.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/29 09:13:33 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/30 10:27:00 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Validate redirection syntax */
t_syntax_error	validate_redir_syntax(t_ast_node *node)
{
	if (!node->left || !node->right
	|| node->right->type != TOKEN_WORD)
		return (SYNTAX_INVALID_COMBINATION);
	if (!node->left && node->right != TOKEN_WORD
		&& node->left->type != TOKEN_REDIR_IN
		&& node->left->type != TOKEN_REDIR_OUT
		&& node->left->type != TOKEN_HEREDOC
		&& node->left->type != TOKEN_APPEND)
		return (SYNTAX_INVALID_COMBINATION);
	return (SYNTAX_OK);
}
