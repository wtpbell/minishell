/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pipe.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 11:37:43 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/15 18:07:21 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "parser.h"
#include "executor.h"
#include "common.h"

static void	handle_child_process(t_child_info *child, \
			t_ast_node *node, t_env **env, t_token *tokens)
{
	signals_child();
	redirect_io(child->input, child->output, child->new_input);
	if (child->saved_stdin != -1 && child->saved_stdin != STDIN_FILENO)
		close(child->saved_stdin);
	set_exit_status(executor_status(node, env, tokens, 1));
	get_root_node(NULL);
	exit_shell(get_exit_status(), node, env, tokens);
}

pid_t	spawn_process(t_child_info *child, int pipe_fd[2], \
		t_ast_node *node, t_env **env)
{
	pid_t	pid;

	child->output = pipe_fd[1];
	child->new_input = pipe_fd[0];
	pid = fork();
	if (pid == 0)
		handle_child_process(child, node, env, child->tokens);
	else if (pid < 0)
	{
		error("fork", NULL);
		if (pipe_fd[0] != STDIN_FILENO)
			close(pipe_fd[0]);
		if (pipe_fd[1] != STDOUT_FILENO)
			close(pipe_fd[1]);
		if (child->saved_stdin != STDIN_FILENO)
			close(child->saved_stdin);
		return (-1);
	}
	if (pipe_fd[1] != STDOUT_FILENO)
		close(pipe_fd[1]);
	return (pid);
}

static void	cleanup_pipe(t_child_info *child, int pipe_fd[2])
{
	if (pipe_fd[1] != STDOUT_FILENO)
		close(pipe_fd[1]);
	if (pipe_fd[0] != STDIN_FILENO)
		close(pipe_fd[0]);
	if (child->input != 0)
		close(child->input);
}

pid_t	launch_pipe(t_child_info *child, int pipe_fd[2], \
		t_ast_node *node, t_env **env)
{
	pid_t		pid;
	pid_t		last_pid;

	last_pid = -1;
	while (node && node->type == TOKEN_PIPE)
	{
		if (pipe(pipe_fd) == -1)
			return (error("pipe", NULL), -1);
		pid = spawn_process(child, pipe_fd, node->left, env);
		if (pid == -1)
			return (cleanup_pipe(child, pipe_fd), -1);
		if (child->input > 0)
			close(child->input);
		close(pipe_fd[1]);
		child->input = pipe_fd[0];
		node = node->right;
		last_pid = pid;
	}
	if (node)
		last_pid = final_process(child, node, env);
	close(child->saved_stdin);
	return (last_pid);
}
