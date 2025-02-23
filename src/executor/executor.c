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

int	executor_status(t_ast_node *node, t_env **env)
{
	t_redir	*redir;

	if (!node || !env)
		return (EXIT_FAILURE);
	redir = node->redirections;
	if (node->type == TOKEN_AND || node->type == TOKEN_OR)
		return (exec_ctrl(node, env));
	else if (redir)
		return (exec_redir(node, env, redir));
	else if (node->type == TOKEN_PIPE)
		return (exec_pipe(node, env));
	else if (node->type == TOKEN_BLOCK)
		return (exec_block(node, env));
	else if (node->type == TOKEN_EXEC)
		return (exec_cmd(node, env));
	return (EXIT_FAILURE);
}

void	executor(t_ast_node *node, t_env **env)
{
	if (!node || !env)
		return ;
	set_exit_status(executor_status(node, env));
}
