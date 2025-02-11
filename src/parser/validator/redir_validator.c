/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_validator.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/29 09:13:33 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/11 10:35:53 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Validate redirection syntax */
t_syntax_error	validate_redir_syntax(t_ast_node *node)
{
	if (!node)
		return (SYNTAX_INVALID_COMBINATION);
	if (node->type == TOKEN_REDIR_IN || node->type == TOKEN_REDIR_OUT
		|| node->type == TOKEN_HEREDOC || node->type == TOKEN_APPEND)
	{
		if (!node->left || (node->right && node->right->type != TOKEN_WORD))
			return (SYNTAX_INVALID_COMBINATION);
	}
	return (SYNTAX_OK);
}
