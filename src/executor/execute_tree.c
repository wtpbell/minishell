/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_tree.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/22 19:15:21 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/22 19:15:21 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "executor.h"
#include "minishell.h"
#include <fcntl.h>

int	exec_ctrl(t_ast_node *node)
{

}

int	exec_block(t_ast_node *node)
{

}

int	exec_pipe(t_ast_node *node)
{

}

int	exec_redir(t_ast_node *node)
{

}

int exec_cmd(t_ast_node *node)
{
	pid_t pid;
	int status;

	if (!node || !node->args)
		return (g_exit_status = EXIT_FAILURE);
	if (is_builtin(node->args[0]))
		return (g_exit_status = execute_builtin(node->args, get_env_list()));
	apply_redirections(node->redirections);
	pid = fork();
	if (pid == 0)
	{
		execve(node->args[0], node->args, rebuild_env_to_char(*get_env_list()));
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return WEXITSTATUS(status);
	}
	else
	{
		perror("fork failed");
		return (g_exit_status = EXIT_FAILURE);
	}
}
