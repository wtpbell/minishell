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

#include "expander.h"
#include "executor.h"
#include "env.h"
#include "minishell.h"
#include "parser.h"
#include "common.h"
#include <fcntl.h>

int	exec_ctrl(t_ast_node *node, t_env **env, t_token *tokens)
{
	int	status_;

	status_ = 0;
	if (node->type == TOKEN_AND)
	{
		if (node->left)
			status_ = executor_status(node->left, env, tokens, 1);
		if (status_ == EXIT_SUCCESS)
			status_ = executor_status(node->right, env, tokens, 1);
	}
	else if (node->type == TOKEN_OR)
	{
		status_ = executor_status(node->left, env, tokens, 1);
		if (status_ != EXIT_SUCCESS)
			status_ = executor_status(node->right, env, tokens, 1);
	}
	set_exit_status(status_);
	return (status_);
}

int	exec_block(t_ast_node *node, t_env **env, t_token *tokens)
{
	int		status_;
	pid_t	pid;

	status_ = 0;
	signal_clear_all();
	pid = fork();
	if (pid == -1)
		return (error("fork() failed", NULL),
			free_exit_memory(node, env, tokens), EXIT_FAILURE);
	else if (pid == 0)
	{
		signals_child();
		status_ = executor_status(node->left, env, tokens, 1);
		set_exit_status(status_);
		free_exit_memory(node, env, tokens);
		exit(status_);
	}
	status_ = wait_for_child();
	set_exit_status(status_);
	return (status_);
}

int	exec_pipe(t_ast_node *node, t_env **env, t_token *tokens)
{
	pid_t			last_pid;
	int				status_;
	int				input;
	int				pipe_fd[2];
	t_child_info	child;

	input = 0;
	signal_clear_all();
	child_init(&child, input, tokens);
	last_pid = launch_pipe(&child, pipe_fd, node, env);
	status_ = wait_for_pid(last_pid);
	wait_for_remain();
	if (child.saved_stdin != -1)
	{
		dup2(child.saved_stdin, STDIN_FILENO);
		close(child.saved_stdin);
	}
	set_exit_status(status_);
	return (status_);
}

int	exec_redir(t_ast_node *node, t_env **env, t_token *tokens, bool error_)
{
	int			saved_fd[2];
	int			status_;
	t_redir		*cur_redir;
	bool		redir_error;

	cur_redir = node->redirections;
	saved_fd[0] = -1;
	saved_fd[1] = -1;
	expand_redir_wildcards(cur_redir);
	redir_error = false;
	while (cur_redir && !redir_error)
	{
		launch_redir(cur_redir, saved_fd, error_);
		if (get_exit_status() != 0)
			redir_error = true;
		cur_redir = cur_redir->next;
	}
	if (!redir_error)
		status_ = exec_cmd(node, env, tokens);
	else
		status_ = get_exit_status();
	restore_redirection(saved_fd);
	cleanup_heredocs(node->redirections);
	return (status_);
}

int	exec_cmd(t_ast_node *node, t_env **env, t_token *tokens)
{
	int		(*builtin)(t_ast_node *node, t_env **env, t_token *tokens);
	int		status_;

	if (!node || !env || !node->args)
		return (set_exit_status(0), 0);
	if (!is_kill_zero(node))
		return (0);
	if (!node->args[0] || node->args[0][0] == '\0')
		return (set_exit_status(127), \
				error(node->args[0], "command not found"), 127);
	expander(node, env);
	if (!node->args[0] || node->args[0][0] == '\0')
		return (set_exit_status(0), 0);
	builtin = is_builtin(node->args[0]);
	if (builtin)
		return (set_exit_status(builtin(node, env, tokens)), get_exit_status());
	status_ = check_cmd(node, env);
	if (status_ != 0)
		return (status_);
	status_ = launch_external_cmd(node, env, tokens);
	return (status_);
}
