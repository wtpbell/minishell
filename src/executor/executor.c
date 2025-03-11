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

// void	executor(t_ast_node *node, t_env **env, t_token *tokens) // For checking redir
// {
// 	int i;
// 	t_redir *redir;

// 	if (!node)
// 	{
// 		printf("executor: received NULL node\n");
// 		return ;
// 	}
// 	// Checking for redirections
// 	if (node->type == 19)
// 	{
// 		redir = node->redirections;
// 		printf("executor: processing redirections\n");
// 		while (redir)
// 		{
// 			if (redir->type == TOKEN_REDIR_IN)
// 				printf("executor: input redirection from file: \"%s\"\n", redir->file);
// 			else if (redir->type == TOKEN_REDIR_OUT)
// 				printf("executor: output redirection to file: \"%s\"\n", redir->file);
// 			else if (redir->type == TOKEN_HEREDOC)
// 				printf("executor: heredoc redirection with file: \"%s\"\n", redir->file);
// 			else if (redir->type == TOKEN_APPEND)
// 				printf("executor: append redirection to file: \"%s\"\n", redir->file);

// 			redir = redir->next;
// 		}
// 	}
// 	// For pipe node processing
// 	if (node->type == 1)
// 	{
// 		printf("executor: processing pipe node\n");
// 		if (node->left)
// 		{
// 			printf("executor: left command = %s\n", node->left->args ? node->left->args[0] : "NULL");
// 			if (node->left->args)
// 			{
// 				for (i = 0; node->left->args[i]; i++)
// 					printf("executor: left argument %d: \"%s\"\n", i, node->left->args[i]);
// 			}
// 		}
// 		if (node->right)
// 		{
// 			printf("executor: right command = %s\n", node->right->args ? node->right->args[0] : "NULL");
// 			if (node->right->args)
// 			{
// 				for (i = 0; node->right->args[i]; i++)
// 					printf("executor: right argument %d: \"%s\"\n", i, node->right->args[i]);
// 			}
// 		}
// 	}
// 	else // Regular command node
// 	{
// 		printf("executor: processing command node of type %d\n", node->type);
// 		if (node->args)
// 		{
// 			printf("executor: command = %s\n", node->args[0]);
// 			printf("executor: arguments = ");
// 			for (i = 0; node->args[i]; i++)
// 				printf("\"%s\" ", node->args[i]);
// 			printf("\n");
// 		}
// 	}
// 	set_exit_status(executor_status(node, env, tokens, 1));
// }

