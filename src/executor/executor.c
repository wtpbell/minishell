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
	int saved_fd[2];

	if (!node)
		return 0;
	if (node->redirections)
	{
		saved_fd[0] = -1;
		saved_fd[1] = -1;
		handle_all_heredocs(node->redirections, saved_fd);
		int error = *heredoc_error();
		if (error != -1)
			return (130);
		restore_redirection(saved_fd);
	}
	if (node->type == TOKEN_PIPE || node->type == TOKEN_AND || node->type == TOKEN_OR)
	{
		if (process_all_heredocs_in_ast(node->left) != 0)
			return (130);
		return process_all_heredocs_in_ast(node->right);
	}
	else if (node->type == TOKEN_BLOCK)
		return process_all_heredocs_in_ast(node->left);
	else if (node->type == TOKEN_EXEC)
		return (0);
	return 0;
}



int	executor_status(t_ast_node *node, t_env **env)
{
	t_redir	*redir;

	if (!node || !env)
		return (EXIT_FAILURE);
	redir = node->redirections;
	printf("Processing node of type: %d\n", node->type);
	if (process_all_heredocs_in_ast(node) != 0) {
		printf("Heredoc error detected\n");
		return (130);
	}
	if (node->type == TOKEN_AND || node->type == TOKEN_OR)
		return (exec_ctrl(node, env));
	else if (redir)
	{
		printf("Redirection detected, executing redirection...\n");
		return (exec_redir(node, env, redir));
	}
	else if (node->type == TOKEN_PIPE)
	{
		printf("Processing pipe node\n");
		return (exec_pipe(node, env));
	}
	else if (node->type == TOKEN_BLOCK)
	{
		printf("Processing block node\n");
		return (exec_block(node, env));
	}
	else if (node->type == TOKEN_EXEC)
	{
		printf("Processing exec node\n");
		return (exec_cmd(node, env));
	}
	printf("Unknown node type\n");
	return (EXIT_FAILURE);
}


void	executor(t_ast_node *node, t_env **env)
{
	if (!node || !env)
		return ;
	set_exit_status(executor_status(node, env));
}

// void executor(t_ast_node *node, t_env **env) //for checking
// {
// 	int i;

// 	if (!node)
// 	{
// 		printf("executor: received NULL node\n");
// 		return ;
// 	}
// 	printf("executor: processing node of type %d\n", node->type);
// 	if (node->args)
// 	{
// 		printf("executor: command = %s\n", node->args[0]);
// 		printf("executor: arguments = ");
// 		for (i = 0; node->args[i]; i++)
// 		printf("\"%s\" ", node->args[i]);
// 		printf("\n");
// 	}
// 	if (!node || !env)
// 		return ;
// 	set_exit_status(executor_status(node, env));
// }
