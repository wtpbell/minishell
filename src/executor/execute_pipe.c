/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pipe.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 11:37:43 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/06 12:03:19 by bewong        ########   odam.nl         */
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

	printf("try to handle redirections in pipe\n");
	last_heredoc = NULL;
	tmp = curr;
	while (tmp)
	{
		printf("tmp->type: %d, tmp->file: %s\n", tmp->type, tmp->file ? tmp->file : "NULL");
		if (tmp->type == TOKEN_HEREDOC)
			last_heredoc = tmp;
		tmp = tmp->next;
	}
	while (curr)
	{
		printf("curr->type: %d, curr->file: %s\n", curr->type, curr->file ? curr->file : "NULL");
		if (curr->type != TOKEN_HEREDOC)
			launch_redir(curr, saved_fd);
		if (curr->heredoc_processed)
		{
			printf("curr->heredoc_processed: %d\n", curr->heredoc_processed);
			handle_heredoc(curr, last_heredoc, saved_fd);
		}
		curr = curr->next;
	}
}

static void	handle_child_process(t_child_info *child, \
			t_ast_node *node, t_env **env, t_token *tokens)
{
	int		saved_fd[2];
	t_redir	*curr;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	redirect_io(child->input, child->output, child->new_input);
	// printf("1curr->type: %d, 1curr->file: %s\n", curr->type, curr->file ? curr->file : "NULL");
	if (node->redirections)
	{
		printf("node->type: %d, node->file: %s\n", node->redirections->type, node->redirections->file ? node->redirections->file : "NULL");
		saved_fd[0] = -1;
		saved_fd[1] = -1;
		curr = node->redirections;
		printf("2curr->type: %d, 2curr->file: %s\n", curr->type, curr->file ? curr->file : "NULL");
		handle_redirections(curr, saved_fd);
	}
	set_exit_status(executor_status(node, env, tokens));
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
		printf("in spawn node->type: %d, node->file: %s\n", node->redirections->type, node->redirections->file ? node->redirections->file : "NULL");
		handle_child_process(child, node, env, child->tokens);
		exit_shell(get_exit_status(), node, env, child->tokens);
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
