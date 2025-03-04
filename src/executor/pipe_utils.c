/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/03 11:45:44 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/04 23:53:33 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	redirect_io(int input, int output, int new_input)
{
	if (new_input != 0)
		close(new_input);
	if (input != 0)
	{
		if (dup2(input, STDIN_FILENO) == -1)
		{
			perror("dup2 failed on input");
			exit(EXIT_FAILURE);
		}
		close(input);
	}
	if (output != 1)
	{
		if (dup2(output, STDOUT_FILENO) == -1)
		{
			perror("dup2 failed on output");
			exit(EXIT_FAILURE);
		}
		close(output);
	}
}

pid_t	final_process(t_child_info *child, \
		t_ast_node *temp, t_env **env)
{
	pid_t	last_pid;
	int		final_pipe[2];

	final_pipe[1] = STDOUT_FILENO;
	final_pipe[0] = 0;
	last_pid = spawn_process(child, final_pipe, temp, env);
	if (child->input != 0)
		close(child->input);
	return (last_pid);
}

void	child_init(t_child_info *child, int input, t_token *tokens)
{
	child->input = input;
	child->output = -1;
	child->new_input = -1;
	child->tokens = tokens;
}

size_t	count_pipes(t_ast_node *node)
{
	size_t	count;

	count = 0;
	while (node)
	{
		if (node->type == TOKEN_PIPE)
			count++;
		node = node->right;
	}
	return (count);
}
