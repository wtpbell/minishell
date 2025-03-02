/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pipe.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 11:37:43 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/03 00:42:30 by bewong        ########   odam.nl         */
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
	int	heredoc_fd;

	heredoc_fd = open(curr->heredoc_file, O_RDONLY);
	if (heredoc_fd == -1)
	{
		error("Failed to open heredoc file", NULL);
		return ;
	}
	if (curr == last_heredoc)
	{
		if (saved_fd[STDIN_FILENO] == -1)
			saved_fd[STDIN_FILENO] = dup(STDIN_FILENO);
		if (dup2(heredoc_fd, STDIN_FILENO) == -1)
		{
			perror("Failed to redirect stdin to heredoc");
			close(heredoc_fd);
			return ;
		}
	}
	close(heredoc_fd);
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
	t_child_info	child;

	child.input = input;
	child.output = pipe_fd[1];
	child.new_input = pipe_fd[0];
	pid = fork();
	if (pid == 0)
	{
		handle_child_process(&child, node, env);
		exit(get_exit_status());
	} 
	else if (pid < 0)
	{
		error("fork", NULL);
		return (-1);
	}
	if (pipe_fd[1] != STDOUT_FILENO)
		close(pipe_fd[1]);
	return (pid);
}

static pid_t	final_process(int input, t_ast_node *temp_node, t_env **env)
{
	pid_t	last_pid;
	int		final_pipe[2];

	final_pipe[1] = STDOUT_FILENO;
	final_pipe[0] = 0;
	last_pid = spawn_process(input, final_pipe, temp_node, env);
	if (input != 0)
		close(input);
	return last_pid;
}

pid_t	launch_pipe(int input, int pipe_fd[2], t_ast_node *temp_node, t_env **env)
{
	pid_t	pid;
	pid_t	last_pid;
	int		final_pipe[2];

	last_pid = -1;
	while (temp_node && temp_node->left && temp_node->type == TOKEN_PIPE)
	{
		if (pipe(pipe_fd) == -1)
			return (error("pipe", NULL), -1);
		pid = spawn_process(input, pipe_fd, temp_node->left, env);
		if (pid == -1)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			break ;
		}
		if (input != 0)
			close(input);
		close(pipe_fd[1]);
		input = pipe_fd[0];
		temp_node = temp_node->right;
		last_pid = pid;
	}
	if (temp_node)
		last_pid = spawn_process(input, final_pipe, temp_node, env);
	return (last_pid);
}
