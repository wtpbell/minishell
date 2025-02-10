/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipeline_handler.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:55:20 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/10 10:21:36 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast_node	*parse_pipe_sequence(t_token **token)
{
	t_ast_node	*left;
	t_ast_node	*pipe_node;
	t_ast_node	*right;
	t_ast_node	*redir;

	if (!token || !*token)
		return (NULL);
	if ((*token)->type == TOKEN_WORD)
	{
		left = parse_command(token);
		if (!left)
			return (NULL);
		if (*token && is_redirection(*token))
		{
			redir = parse_redirection(token);
			if (!redir)
			{
				free_ast(left);
				return (NULL);
			}
			redir->left = left;
			left = redir;
		}
	}
	else
		return (NULL);
	if (!*token || (*token)->type != TOKEN_PIPE)
		return (left);
	pipe_node = create_ast_node(TOKEN_PIPE);
	if (!pipe_node)
	{
		free_ast(left);
		return (NULL);
	}
	*token = (*token)->next;
	right = parse_pipe_sequence(token);
	if (!right)
	{
		free_ast(left);
		free_ast(pipe_node);
		return (NULL);
	}
	pipe_node->left = left;
	pipe_node->right = right;
	return (pipe_node);
}

t_ast_node	*parse_pipeline(t_token **token)
{
	t_ast_node	*root;
	t_ast_node	*current;

	if (!token || !*token)
		return (NULL);
	printf("Starting pipeline parse with token: type=%d, content='%s'\n",
		(*token)->type, (*token)->content);
	root = parse_pipe_sequence(token);
	if (!root)
		return (NULL);
	current = root;
	while (current)
	{
		if (current->type == TOKEN_PIPE && (!current->left || !current->right))
		{
			printf("Invalid pipeline structure detected\n");
			free_ast(root);
			return (NULL);
		}
		current = current->right;
	}
	return (root);
}
