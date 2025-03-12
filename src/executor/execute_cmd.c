/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_cmd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 17:04:08 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/12 17:24:11 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "parser.h"
#include "common.h"
#include "expander.h"

int	launch_builtin(t_ast_node *node, t_env **env, t_token *tokens)
{
	int	status;
	int	(*builtin)(t_ast_node *node, t_env **env, t_token *tokens);

	builtin = is_builtin(node->args[0]);
	if (builtin)
	{
		status = builtin(node, env, tokens);
		set_exit_status(status);
		return (status);
	}
	return (-1);
}

int	launch_external(t_ast_node *node, t_env **env, t_token *tokens)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork failed"), free_exit_memory(node, env, tokens), \
		EXIT_FAILURE);
	if (pid == 0)
		child(node, env);
	status = wait_for_pid(pid);
	signals_init();
	return (status);
}

int	expand_and_validate(t_ast_node *node, t_env **env)
{
	expander(node, env);
	if (!node->args[0] || node->args[0][0] == '\0')
		return (set_exit_status(127), error(node->args[0], \
		"Command not found"), 127);
	return (0);
}
