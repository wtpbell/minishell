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
#include "common.h"

static int	process_all_heredocs_in_ast(t_ast_node *node)
{
	int	saved_fd[2];

	if (!node)
		return (0);
	if (node->redirections)
	{
		saved_fd[0] = -1;
		saved_fd[1] = -1;
		handle_all_heredocs(node->redirections, saved_fd);
		if (get_exit_status() == 130)
			return (130);
		restore_redirection(saved_fd);
	}
	if (node->type == TOKEN_PIPE || node->type == TOKEN_AND \
		|| node->type == TOKEN_OR)
	{
		if (process_all_heredocs_in_ast(node->left) != 0)
			return (130);
		return (process_all_heredocs_in_ast(node->right));
	}
	else if (node->type == TOKEN_BLOCK)
		return (process_all_heredocs_in_ast(node->left));
	else if (node->type == TOKEN_EXEC)
		return (0);
	return (0);
}

int	executor_status(t_ast_node *node, t_env **env, t_token *tokens, bool error_)
{
	if (!node || !env)
		return (EXIT_FAILURE);
	if (process_all_heredocs_in_ast(node) != 0)
		return (130);
	if (node->type == TOKEN_AND || node->type == TOKEN_OR)
		return (exec_ctrl(node, env, tokens));
	else if (node->redirections)
		return (exec_redir(node, env, tokens, error_));
	else if (node->type == TOKEN_PIPE)
		return (exec_pipe(node, env, tokens));
	else if (node->type == TOKEN_BLOCK)
		return (exec_block(node, env, tokens));
	else if (node->type == TOKEN_EXEC)
		return (exec_cmd(node, env, tokens));
	return (EXIT_FAILURE);
}

void	executor(t_ast_node *node, t_env **env, t_token *tokens)
{
	if (!node || !env)
		return ;
	set_exit_status(executor_status(node, env, tokens, 1));
}
