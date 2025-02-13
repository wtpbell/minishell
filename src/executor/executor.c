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
	// printf("executor_status: processing node of type %d\n", node->type);
	if (node->type == TOKEN_EXEC)
		return (exec_cmd(node));
	else if (node->type == TOKEN_PIPE)
		return (exec_pipe(node));
	else if (node->type == TOKEN_AND || node->type == TOKEN_OR)
		return (exec_ctrl(node));
	else if (node->type ==  (TOKEN_REDIR_IN) || node->type ==  (TOKEN_REDIR_OUT)
			|| node->type == TOKEN_APPEND || node->type == TOKEN_HEREDOC)
		return (exec_redir(node));
	else if (node->type == TOKEN_BLOCK)
		return (exec_block(node));
	return (EXIT_FAILURE);
}

// void	executor(t_ast_node *node)
// {
// 	if (!node)
// 		return ;
// 	set_exit_status(executor_status(node));
// }

void	executor(t_ast_node *node) // For checking redir
{
	int i;
	t_redirection *redir;

	if (!node)
	{
		printf("executor: received NULL node\n");
		return ;
	}
	// Checking for redirections
	if (node->type == 19)
	{
		redir = node->redirections;
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
	set_exit_status(executor_status(node));
}







