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
	{
		// printf("did i come to redir\n");
		return (exec_redir(node, env, redir));
	}
	else if (node->type == TOKEN_PIPE)
		return (exec_pipe(node, env));
	else if (node->type == TOKEN_BLOCK)
		return (exec_block(node, env));
	else if (node->type == TOKEN_EXEC)
	{
		// printf("did i come to exec_cmd\n");
		return (exec_cmd(node, env));
	}
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
