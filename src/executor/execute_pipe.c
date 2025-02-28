/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pipe.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 11:37:43 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/28 23:30:31 by bewong        ########   odam.nl         */
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

static int	handle_heredocs(t_redir *redirections)
{
	int saved_fd[2];

	saved_fd[0] = -1;
	saved_fd[1] = -1;
	handle_all_heredocs(redirections, saved_fd);
	if (get_exit_status() == 130)
		return (-1);
	restore_redirection(saved_fd);
	return (0);
}

static void	handle_redirections(t_redir *curr, int saved_fd[2])
{
	int	fd;

	while (curr)
	{
		if (curr->type != TOKEN_HEREDOC)
			launch_redir(curr, saved_fd);
		else
		{
			fd = open(curr->file, curr->flags, 0644);
			if (fd != -1)
			{
				if (saved_fd[curr->fd] == -1)
					saved_fd[curr->fd] = dup(curr->fd);
				dup2(fd, curr->fd);
				close(fd);
			}
		}
		curr = curr->next;
	}
}

static void	handle_child_process(int input, int output, int new_input, t_ast_node *node, t_env **env)
{
	int		saved_fd[2];
	t_redir	*curr;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	redirect_io(input, output, new_input);
	if (node->redirections)
	{
		saved_fd[0] = -1;
		saved_fd[1] = -1;
		curr = node->redirections;
		handle_redirections(curr, saved_fd);
	}
	set_exit_status(executor_status(node, env));
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

pid_t	spawn_process(int input, int pipe_fd[2], t_ast_node *node, t_env **env)
{
	pid_t	pid;
	int		output;
	int		new_input;

	output = pipe_fd[1];
	new_input = pipe_fd[0];
	pid = fork();
	if (pid == 0)
	{
		handle_child_process(input, output, new_input, node, env);
		exit(get_exit_status());
	}
	else if (pid < 0)
	{
		error("fork", NULL);
		exit(1);
	}
	if (input != 0)
		close(input);
	return (pid);
}

static int	handle_all_heredocs_for_pipes(t_ast_node *temp_node)
{
	while (temp_node && temp_node->type == TOKEN_PIPE)
	{
		if (temp_node->left && temp_node->left->redirections)
		{
			if (handle_heredocs(temp_node->left->redirections) == -1)
				return (-1);
		}
		temp_node = temp_node->right;
	}
	if (temp_node && temp_node->redirections)
	{
		if (handle_heredocs(temp_node->redirections) == -1)
			return (-1);
	}
	return (0);
}

static pid_t	handle_pipe_chain(int input, int pipe_fd[2], \
					t_ast_node *temp_node, t_env **env)
{
	while (temp_node && temp_node->left && temp_node->type == TOKEN_PIPE)
	{
		if (pipe(pipe_fd) == -1)
		{
			error("pipe", NULL);
			exit(1);
		}
		spawn_process(input, pipe_fd, temp_node->left, env);
		close(pipe_fd[1]);
		input = pipe_fd[0];
		temp_node = temp_node->right;
	}
	pipe_fd[1] = 1;
	pipe_fd[0] = 0;
	return (spawn_process(input, pipe_fd, temp_node, env));
}

pid_t	launch_pipe(t_ast_node *node, t_env **env)
{
	int			input;
	int			pipe_fd[2];
	t_ast_node	*temp_node;

	input = 0;
	signal(SIGINT, interrput_silence);
	signal(SIGQUIT, interrput_silence);
	temp_node = node;
	if (handle_all_heredocs_for_pipes(temp_node) == -1)
		return (-1);
	return (handle_pipe_chain(input, pipe_fd, temp_node, env));
}

