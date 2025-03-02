/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pipe.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 11:37:43 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/02 21:20:55 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "parser.h"
#include "executor.h"
#include "common.h"

static void	handle_heredoc(t_redir *curr, \
			t_redir *last_heredoc, int saved_fd[2])
{
	int	fd;

	fd = open(curr->heredoc_file, O_RDONLY);
	if (fd == -1)
	{
		error("Failed to open heredoc file", NULL);
		return ;
	}
	if (curr == last_heredoc)
	{
		if (saved_fd[STDIN_FILENO] == -1)
			saved_fd[STDIN_FILENO] = dup(STDIN_FILENO);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("Failed to redirect stdin to heredoc");
			close(fd);
			return ;
		}
	}
	close(fd);
}

static void	handle_redirections(t_redir *curr, int saved_fd[2])
{
	t_redir	*last_heredoc;
	t_redir	*tmp;

	last_heredoc = NULL;
	tmp = curr;
	while (tmp)
	{
		if (tmp->type == TOKEN_HEREDOC)
			last_heredoc = tmp;
		tmp = tmp->next;
	}
	while (curr)
	{
		if (curr->type != TOKEN_HEREDOC)
			launch_redir(curr, saved_fd);
		else if (curr->heredoc_processed)
			handle_heredoc(curr, last_heredoc, saved_fd);
		curr = curr->next;
	}
}

static void	handle_child_process(t_child_info *child, t_ast_node *node, t_env **env)
{
	int		saved_fd[2];
	t_redir	*curr;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (child->new_input != 0)
		close(child->new_input);
	if (child->input != 0)
	{
		dup2(child->input, STDIN_FILENO);
		close(child->input);
	}
	if (child->output != 1)
	{
		dup2(child->output, STDOUT_FILENO);
		close(child->output);
	}
	if (node->redirections)
	{
		saved_fd[0] = -1;
		saved_fd[1] = -1;
		curr = node->redirections;
		handle_redirections(curr, saved_fd);
	}
	set_exit_status(executor_status(node, env));
}

pid_t	spawn_process(int input, int pipe_fd[2], t_ast_node *node, \
					t_env **env)
{
	pid_t			pid;
	int				status_;
	t_child_info	child;

	child.input = input;
	child.output = pipe_fd[1];
	child.new_input = pipe_fd[0];
	pid = fork();
	if (pid == 0)
	{
		// fprintf(stderr, "Executing child process: %s\n", node->args[0]);
		// printf("Pipe created: pipe_fd[0] = %d, pipe_fd[1] = %d\n", pipe_fd[0], pipe_fd[1]);
		handle_child_process(&child, node, env);
		exit(get_exit_status());
	} 
	else if (pid < 0)
	{
		// printf("Error fork in spawn: %d\n", get_exit_status());
		error("fork", NULL);
		return (-1);
	}
	close(pipe_fd[1]);
	// printf("Parent: Waiting for child process to finish\n");
	// printf("Waiting for child process (pid: %d)\n", pid);
	waitpid(pid, &status_, 0);
	// printf("Parent: Child process finished\n");
	return (pid);
}

pid_t	launch_pipe(int input, int pipe_fd[2], t_ast_node *temp_node, t_env **env)
{
	// printf("Entering launch_pipe with input: %d\n", input);
	while (temp_node && temp_node->left && temp_node->type == TOKEN_PIPE)
	{
		if (pipe(pipe_fd) == -1)
		{
			error("pipe", NULL);
			return (-1);
		}
		spawn_process(input, pipe_fd, temp_node->left, env);
		close(pipe_fd[1]);
		input = pipe_fd[0];
		temp_node = temp_node->right;
	}
	pipe_fd[1] = 1;
	pipe_fd[0] = 0;
	close(pipe_fd[0]);
	return (spawn_process(input, pipe_fd, temp_node, env));
}



