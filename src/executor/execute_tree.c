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
	These are typically used in shell commands to control the flow of
	execution based on the success or failure of the previous command.
	AND Operator (&&): The second command runs only if the first one succeeds.
	OR Operator (||): The second command runs only if the first one fails
*/
int	exec_ctrl(t_ast_node *node)
{
	int	status_;

	status_ = 0;
	if (node->type == TOKEN_AND)
	{
		if (node->left)
			status_ = executor_status(node->left);
		if (status_ == EXIT_SUCCESS)
			status_ = executor_status(node->right);
	}
	else if (node->type == TOKEN_OR)
	{
		status_ = executor_status(node->left);
		if (status_ != EXIT_SUCCESS)
			status_ = executor_status(node->right);
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
int	exec_block(t_ast_node *node)
{
	int	status_;
	pid_t	pid;

	status_ = 0;
	signal(SIGINT, interrput_silence);
	signal(SIGQUIT, interrput_silence);
	pid = fork();
	if (pid== -1)
		return (error("fork() failed", NULL), EXIT_FAILURE);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		status_ = executor_status(node->left);
		set_exit_status(status_);
		free_all_memory();
		exit(status_);
	}
	wait(&status_);
	if (WIFEXITED(status_))
		status_ = WEXITSTATUS(status_);
	else
		status_ = EXIT_FAILURE;
	set_exit_status(status_);
	signals_init();
	printf("print status: %d\n", status_);
	return (status_);
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
	This function must open a file for redirection and updates the file descriptors.
	It performs the redirection before executing the command and restores
	the original file descriptor afterward.
*/
int	exec_redir(t_ast_node *node)
{
	int	fd;
	int	saved_fd;
	int	status_;

	if (!node)
		return (0);
	if (node->right && exec_redir(node->right) != 0)
		return (1);
	fd = open(node->args[0], get_redirection_flags(node->type), 0644);
	if (fd == -1)
		return (error(node->args[0], NULL), set_exit_status(1), 1);
	saved_fd = dup(get_redirection_fd(node->type));
	if (saved_fd == -1)
		return (error("dup failed", NULL), close(fd), set_exit_status(1), 1);
	if (dup2(fd, get_redirection_fd(node->type)) == -1)
		return (error("dup2 failed", NULL), close(fd), set_exit_status(1), 1);
	close(fd);
	status_ = executor_status(node->left);
	if (dup2(saved_fd, get_redirection_fd(node->type)) == -1)
		return (error("dup2 restore failed", NULL), close(saved_fd), set_exit_status(1), 1);
	close(saved_fd);
	if (node->type == TOKEN_HEREDOC)
		unlink(node->args[0]);
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

