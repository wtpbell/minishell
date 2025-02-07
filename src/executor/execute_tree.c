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

#include "env.h"
#include "minishell.h"
#include "parser.h"
#include "executor.h"
#include "common.h"
#include <fcntl.h>

/*
	The exec_ctrl() handles the AND (&&) and OR (||) control operators.
	These are typically used in shell commands to control the flow of
	execution based on the success or failure of the previous command.
	AND Operator (&&): The second command runs only if the first one succeeds.
	OR Operator (||): The second command runs only if the first one fails
*/
int	exec_ctrl(t_ast_node *node)
{
	int	(*builtin)(t_ast_node *node);

	builtin = is_builtin(node->args[0]);
	if (builtin)
		return (set_exit_status(builtin(node)), get_exit_status());
	return (1); //temprory
}

/*
	The exec_block() handles executing a block of commands inside
	parentheses () in a shell-like program.
	When a block of commands is executed, it's typically treated
	as a separate process, isolated from the parent shell.
	The function forks a new child process to execute the commands
	in the block and waits for it to complete
*/
int	exec_block(t_ast_node *node)
{
	int	(*builtin)(t_ast_node *node);

	builtin = is_builtin(node->args[0]);
	if (builtin)
		return (set_exit_status(builtin(node)), get_exit_status());
	return (1); //temprory
}

/*
	The exec_pipe() is responsible for handling pipelines of commands
	where the output of one command becomes the input of the next.
	This function sets up a pipeline, forks processes, and connects them via pipes.
	The function waits for the last process in the pipeline to finish, collects 
	the exit status, and returns it.
*/
int	exec_pipe(t_ast_node *node)
{
	pid_t	last_pid;
	int		status_;
	size_t	i;

	printf("Executing pipe node\n");
	set_exit_status(0);
	last_pid = launch_pipe(node);
	waitpid(last_pid, &status_, 0);
	if (WIFEXITED(status_))
		status_ = WEXITSTATUS(status_);
	else
		status_ = EXIT_FAILURE;
	i = 0;
	while (i++ < count_pipes(node) - 1)
		wait(NULL);
	set_exit_status(status_);
	signals_init();
	return (status_);
}

/*
	The exec_redir() handles input/output redirection.
	This function opens a file for redirection and updates the file descriptors.
	It performs the redirection before executing the command and restores
	the original file descriptor afterward.
*/
int	exec_redir(t_ast_node *node)
{
	t_redirection	*redir;
	int				fd;
	int				dup_fd;
	int				status_;
	int				flags;

	if (!node || !node->redirections)
		return (0);
	redir = node->redirections;
	flags = get_redirection_flags(node->type);
	while(redir)
	{
		fd = open(redir->file, flags, 0644);
		if (fd == -1)
		{
			error(redir->file, NULL);
			return (set_exit_status(1), 1);
		}
		dup_fd = dup(fd);
		dup2(fd, fd);
		status_ = executor_status(node);
		set_exit_status(status_);
		close(fd);
		dup2(dup_fd, fd);
		close(dup_fd);
		if (redir->type == TOKEN_HEREDOC)
			unlink(redir->file);
	}
	return (status_);
}

/*
	The exec_cmd() is responsible for executing a single command in the shell,
	which can either be a built-in command or an external command.
	If it's a built-in command, execute it directly.
	If it's an external command, search for it in the system's executable paths
	and run it in a child process.
*/
int exec_cmd(t_ast_node *node)
{
	int	(*builtin)(t_ast_node *node);
	int	status_;

	if (!node || !node->args)
		return (set_exit_status(0), 0);
	if (node->argc == 0)
		return (set_exit_status(0), 0);
	status_ = 0;
	node->env = get_env_list();
	if (node->env == 0)
		return (set_exit_status(0), 0);
	builtin = is_builtin(node->args[0]);
	if (builtin)
		return (set_exit_status(builtin(node)), get_exit_status());
	status_ = check_cmd(node);
	if (status_ != 0)
		return (status_);
	signal(SIGINT, interrupt_w_msg);
	signal(SIGQUIT, interrupt_w_msg);;
	if (fork() == 0)
		child(node);
	return (parent(node));
}
