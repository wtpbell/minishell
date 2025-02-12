/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pipe.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 11:37:43 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/07 10:22:51 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "parser.h"
#include "executor.h"
#include "common.h"

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

pid_t	launch_pipe(t_ast_node *node)
{
	int		input;
	int		pipe_fd[2];
	size_t	i;

	signal(SIGINT, interrput_slience);
	signal(SIGQUIT, interrput_slience);
	i = 0;
	while (node && node->left && node->right)
	{
		if (pipe(pipe_fd) == -1)
		{
			error("pipe", NULL);
			exit(1);
		}
		spawn_process(input, pipe_fd, node->left);
		close(pipe_fd[1]);
		input = pipe_fd[0];
		node = node->right;
		i++;
	}
	pipe_fd[1] = 1;
	pipe_fd[0] = 0;
	return (spawn_process(input, pipe_fd, node));
}

pid_t	spawn_process(int input, int pipe_fd[2], t_ast_node *node)
{
	pid_t	pid;
	int		output;
	int		new_input;

	output = pipe_fd[1];
	new_input = pipe_fd[0];
	pid = fork();
	if (pid == 0)
		child_process(node, input, output, new_input);
	if (input != 0)
		close(input);
	return (pid);
}

void	child_process(t_ast_node *node, int input, int output, int new_input)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	redirect_io(input, output, new_input);
	set_exit_status(executor_status(node));
	free_all_memory();
	exit(get_exit_status());
}

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
