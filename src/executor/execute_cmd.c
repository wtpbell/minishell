/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 21:22:22 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/12 21:24:55 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "executor.h"
#include "env.h"
#include "minishell.h"
#include "parser.h"
#include "common.h"

int	launch_external_cmd(t_ast_node *node, t_env **env, t_token *tokens)
{
	pid_t	pid;
	int		status_;

	signal(SIGINT, interrupt_w_nl);
	signal(SIGQUIT, interrupt_w_nl);
	pid = fork();
	if (pid == -1)
		return (perror("fork failed"), \
			free_exit_memory(node, env, tokens), EXIT_FAILURE);
	if (pid == 0)
		child(node, env);
	status_ = wait_for_pid(pid);
	return (status_);
}
