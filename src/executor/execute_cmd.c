/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 21:22:22 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/16 16:33:43 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include "executor.h"
#include "env.h"
#include "minishell.h"
#include "parser.h"
#include "common.h"

int	is_kill_zero(t_ast_node *node)
{
	if (node->args[0] && ft_strcmp(node->args[0], "kill") == 0 && \
		node->args[1] && ft_strcmp(node->args[1], "0") == 0 && \
		(node->args[2] == NULL || node->args[2][0] == '\0'))
	{
		get_root_node(node);
		signal_clear_all();
		set_exit_status(0);
		get_root_node(NULL);
		kill(0, SIGTERM);
		return (0);
	}
	return (1);
}

int	launch_external_cmd(t_ast_node *node, t_env **env, t_token *tokens)
{
	pid_t	pid;
	int		status_;

	signal_clear_all();
	pid = fork();
	if (pid == -1)
		return (perror("fork failed"), \
			free_exit_memory(node, env, tokens), EXIT_FAILURE);
	if (pid == 0)
		child(node, env);
	status_ = wait_for_pid(pid);
	if (signal_is_set(SIG_RECEIVED_TERM))
		return (0);
	return (status_);
}
