/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/22 11:00:14 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/22 11:00:14 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void executor(t_ast_node *node)
{
	if (!node)
		return;
	if (node->type == TOKEN_EXEC)
		exec_cmd(node);
	else if (node->type == TOKEN_PIPE)
		exec_pipe(node);
	else if (node->type == TOKEN_AND || node->type == TOKEN_OR)
		exec_ctrl(node);
	else if (node->type & (TOKEN_REDIR_IN | TOKEN_REDIR_OUT))
		exec_redir(node);
	else if (node->type == TOKEN_BLOCK)
		exec_block(node);
	if (node->type == TOKEN_PIPE || node->type == TOKEN_AND || node->type == TOKEN_OR)
	{
		executor(node->left);
		executor(node->right);
	}
}

