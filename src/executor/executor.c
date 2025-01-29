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

int	executor_status(t_ast_node *node)
{	
	if (!node)
		return ;
	if (node->type == TOKEN_EXEC)
		return (exec_cmd(node));
	else if (node->type == TOKEN_PIPE)
		return (exec_pipe(node));
	else if (node->type == TOKEN_AND || node->type == TOKEN_OR)
		return (exec_ctrl(node));
	else if (node->type ==  (TOKEN_REDIR_IN) || node->type ==  (TOKEN_REDIR_OUT))
		return (exec_redir(node));
	else if (node->type == TOKEN_BLOCK)
		return (exec_block(node));
}

void	executor(t_ast_node *node)
{
	if (!node)
		return ;
	set_exit_status(executor_status(node));
}
