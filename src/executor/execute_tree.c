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

/*
	These are typically used in shell commands to control the flow of
	execution based on the success or failure of the previous command.
	AND Operator (&&): The second command runs only if the first one succeeds.
	OR Operator (||): The second command runs only if the first one fails
*/
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

/*
	The exec_block() handles executing a block of commands inside
	parentheses () in a shell-like program.
	When a block of commands is executed, it's typically treated
	as a separate process, isolated from the parent shell.
	The function forks a new child process to execute the commands
	in the block and waits for it to complete
*/
int	exec_block(t_ast_node *node, t_env **env, t_token *tokens)
{
	int		status_;
	pid_t	pid;

	status_ = 0;
	signal(SIGINT, interrput_silence);
	signal(SIGQUIT, interrput_silence);
	pid = fork();
	if (pid == -1)
		return (error("fork() failed", NULL),
			free_exit_memory(node, env, tokens), EXIT_FAILURE);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		status_ = executor_status(node->left, env, tokens, 1);
		set_exit_status(status_);
		free_exit_memory(node, env, tokens);
		exit(status_);
	}
	status_ = wait_for_child();
	set_exit_status(status_);
	signals_init();
	return (status_);
}

/*
	The exec_pipe() is responsible for handling pipelines of commands
	where the output of one command becomes the input of the next.
	This function sets up a pipeline, forks processes,
	and connects them via pipes.
	The function waits for the last process in the pipeline to finish, collects
	the exit status, and returns it.
*/
int	exec_pipe(t_ast_node *node, t_env **env, t_token *tokens)
{
	pid_t			last_pid;
	int				status_;
	int				input;
	int				pipe_fd[2];
	t_child_info	child;

	input = 0;
	signal(SIGINT, interrput_silence);
	signal(SIGQUIT, interrput_silence);
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
	signals_init();
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
	signals_init();
	return (status_);
}

/*
	The exec_cmd() is responsible for executing a single command in the shell,
	which can either be a built-in command or an external command.
	If it's a built-in command, execute it directly.
	If it's an external command, search for it in the system's executable paths
	and run it in a child process.
*/

int	exec_cmd(t_ast_node *node, t_env **env, t_token *tokens)
{
	int		(*builtin)(t_ast_node *node, t_env **env, t_token *tokens);
	int		status_;

	if (!node || !node->args || !env || node->argc == 0)
		return (set_exit_status(0), 0);
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
	if (status_)
		return (status_);
	status_ = launch_external_cmd(node, env, tokens);
	signals_init();
	return (status_);
}
