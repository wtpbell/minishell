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

	redir = node->redirections;
	if (!node || !env)
		return (EXIT_FAILURE);
	if (node->type && (node->type == TOKEN_AND || node->type == TOKEN_OR))
		return (exec_ctrl(node, env));
	else if (redir && (redir->type == TOKEN_APPEND || redir->type == TOKEN_HEREDOC
		|| redir->type == TOKEN_REDIR_IN || redir->type == TOKEN_REDIR_OUT))
			return (exec_redir(node, env, redir));
	else if (node->type && node->type == TOKEN_PIPE)
		return (exec_pipe(node, env));
	else if (node->type && node->type == TOKEN_BLOCK)
		return (exec_block(node, env));
	else if (node->type && node->type == TOKEN_EXEC)
		return (exec_cmd(node, env));
	return (EXIT_FAILURE);
}

// void	executor(t_ast_node *node, t_env **env)
// {
// 	if (!node || !env)
// 		return ;
// 	set_exit_status(executor_status(node, env));
// }

void	executor(t_ast_node *node, t_env **env) // For checking redir
{
	int		i;
	t_redir *redir;

	if (!node)
	{
		printf("executor: received NULL node\n");
		return ;
	}
	// Checking for redirections
	redir = node->redirections;
	// printf("%p\n", redir);
	if (redir->type == 3 || redir->type == 2 || redir->type == 4 || redir->type == 5)
	{
		// redir = node->redirections;
		printf("executor: processing redirections\n");
		while (redir)
		{
			if (redir->type == TOKEN_REDIR_IN)
				printf("executor: input redirection from file: \"%s\"\n", redir->file);
			else if (redir->type == TOKEN_REDIR_OUT)
				printf("executor: output redirection to file: \"%s\"\n", redir->file);
			else if (redir->type == TOKEN_HEREDOC)
				printf("executor: heredoc redirection with file: \"%s\"\n", redir->file);
			else if (redir->type == TOKEN_APPEND)
				printf("executor: append redirection to file: \"%s\"\n", redir->file);

			redir = redir->next;
		}
	}
	// For pipe node processing
	if (node->type == 1)
	{
		printf("executor: processing pipe node\n");
		if (node->left)
		{
			printf("executor: left command = %s\n", node->left->args ? node->left->args[0] : "NULL");
			if (node->left->args)
			{
				for (i = 0; node->left->args[i]; i++)
					printf("executor: left argument %d: \"%s\"\n", i, node->left->args[i]);
			}
		}
		if (node->right)
		{
			printf("executor: right command = %s\n", node->right->args ? node->right->args[0] : "NULL");
			if (node->right->args)
			{
				for (i = 0; node->right->args[i]; i++)
					printf("executor: right argument %d: \"%s\"\n", i, node->right->args[i]);
			}
		}
	}
	else // Regular command node
	{
		printf("executor: processing command node of type %d\n", node->type);
		if (node->args)
		{
			printf("executor: command = %s\n", node->args[0]);
			printf("executor: arguments = ");
			for (i = 0; node->args[i]; i++)
				printf("\"%s\" ", node->args[i]);
			printf("\n");
		}
	}
	set_exit_status(executor_status(node, env));
}







