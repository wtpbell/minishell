/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/03 11:45:44 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/03 11:49:59 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	redirect_io(int input, int output, int new_input)
{
	if (new_input != 0)
		close(new_input);
	if (input != 0)
	{
		dup2(input, STDIN_FILENO);
		close(input);
	}
	if (output != 1)
	{
		dup2(output, STDOUT_FILENO);
		close(output);
	}
}

pid_t	final_process(int input, t_ast_node *temp_node, t_env **env)
{
	pid_t	last_pid;
	int		final_pipe[2];

	final_pipe[1] = STDOUT_FILENO;
	final_pipe[0] = 0;
	last_pid = spawn_process(input, final_pipe, temp_node, env);
	if (input != 0)
		close(input);
	return (last_pid);
}
