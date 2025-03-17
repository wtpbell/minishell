/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_process.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/04 18:45:18 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/16 19:18:15 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "parser.h"
#include "executor.h"
#include "common.h"
#include <sys/wait.h>

void	child(t_ast_node *node, t_env **env)
{
	char	**env_arr;

	signals_child();
	env_arr = env_to_arr(*env);
	if (!env_arr)
	{
		perror("env_to_arr failed");
		error(node->args[0], NULL);
		set_exit_status(127);
		exit(127);
	}
	execve(node->args[0], node->args, env_arr);
	error(node->args[0], NULL);
	child_cleanup(node, env_arr);
	set_exit_status(127);
	exit(127);
}
