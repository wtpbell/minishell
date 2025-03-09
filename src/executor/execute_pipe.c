/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pipe.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 11:37:43 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/09 16:46:33 by bewong        ########   odam.nl         */
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

void	handle_redirections(t_redir *curr, int saved_fd[2], int error_)
{
	t_redir	*last_heredoc;
	bool	redir_error;

	redir_error = false;
	last_heredoc = get_last_heredoc(curr);
	while (curr && !redir_error)
	{
		if (curr->type != TOKEN_HEREDOC)
		{
			launch_redir(curr, saved_fd, error_);
			if (get_exit_status() != 0)
				redir_error = true;
		}
		else if (curr->heredoc_processed && !redir_error)
		{
			if (error_)
				handle_heredoc(curr, last_heredoc, saved_fd);
		}
		if (!redir_error)
			curr = curr->next;
		else
			break ;
	}
}

static void	handle_child_process(t_child_info *child, \
			t_ast_node *node, t_env **env, t_token *tokens)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	redirect_io(child->input, child->output, child->new_input);
	set_exit_status(executor_status(node, env, tokens, 1));
}

pid_t	spawn_process(t_child_info *child, int pipe_fd[2], \
		t_ast_node *node, t_env **env)
{
	pid_t	pid;

	child->output = pipe_fd[1];
	child->new_input = pipe_fd[0];
	pid = fork();
	if (pid == 0)
	{
		handle_child_process(child, node, env, child->tokens);
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

/* while loop handle all but bot the last cmd in pipeline */
pid_t	launch_pipe(t_child_info *child, int pipe_fd[2], \
		t_ast_node *temp, t_env **env)
{
	pid_t	pid;
	pid_t	last_pid;

	last_pid = -1;
	while (temp && temp->left && temp->type == TOKEN_PIPE)
	{
		if (pipe(pipe_fd) == -1)
			return (error("pipe", NULL), -1);
		pid = spawn_process(child, pipe_fd, temp->left, env);
		if (pid == -1)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			break ;
		}
		if (child->input != 0)
			close(child->input);
		close(pipe_fd[1]);
		child->input = pipe_fd[0];
		temp = temp->right;
		last_pid = pid;
	}
	if (temp)
		last_pid = final_process(child, temp, env);
	return (last_pid);
}
