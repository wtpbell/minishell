/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pipe.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 11:37:43 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/11 15:14:57 by spyun         ########   odam.nl         */
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
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	redirect_io(child->input, child->output, child->new_input);
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
		return (-1);
	}
	if (pipe_fd[1] != STDOUT_FILENO)
		close(pipe_fd[1]);
	return (pid);
}

/* while loop handle all but bot the last cmd in pipeline */
pid_t	launch_pipe(t_child_info *child, int pipe_fd[2], \
		t_ast_node *node, t_env **env)
{
	pid_t	pid;
	pid_t	last_pid;

	last_pid = -1;
	while (node && node->left && node->type == TOKEN_PIPE)
	{
		if (pipe(pipe_fd) == -1)
			return (error("pipe", NULL), -1);
		pid = spawn_process(child, pipe_fd, node->left, env);
		if (pid == -1)
			break ;
		if (child->input != 0)
			close(child->input);
		child->input = pipe_fd[0];
		node = node->right;
		last_pid = pid;
	}
	if (node)
		last_pid = final_process(child, node, env);
	return (last_pid);
}
