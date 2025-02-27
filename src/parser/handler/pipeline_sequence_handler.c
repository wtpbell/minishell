/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipeline_sequence_handler.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 11:14:04 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/27 11:09:14 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse_pipe_sequence(t_token **token);

static t_ast_node	*handle_pipe_left(t_token **token)
{
	t_ast_node	*left;
	t_ast_node	*redir;

	if ((*token)->type != TOKEN_WORD)
		return (NULL);
	left = parse_command(token);
	if (!left)
		return (NULL);
	if (*token && is_redirection(*token))
	{
		redir = handle_redirection_in_pipe(left, token);
		if (!redir)
		{
			free_ast(left);
			return (NULL);
		}
		left = redir;
	}
	return (left);
}

static t_ast_node	*handle_pipe_redirection(t_token **token)
{
	t_ast_node	*cmd_node;
	t_token		*current;

	cmd_node = create_ast_node(TOKEN_WORD);
	if (!cmd_node)
		return (NULL);
	current = *token;
	while (current && is_redirection(current))
	{
		if (!current->next || current->next->type != TOKEN_WORD)
		{
			free_ast(cmd_node);
			return (NULL);
		}
		add_redirection(cmd_node, current->type, current->next->content);
		current = current->next->next;
	}
	*token = current;
	return (cmd_node);
}

static t_ast_node	*handle_pipe_right(t_token **token, t_ast_node *left)
{
	t_ast_node	*right;
	t_ast_node	*pipe_node;

	*token = (*token)->next;
	if (*token && is_redirection(*token))
		right = handle_pipe_redirection(token);
	else
		right = parse_pipe_sequence(token);
	if (!right)
	{
		free_ast(left);
		return (NULL);
	}
	pipe_node = create_pipe_node(left, right);
	if (!pipe_node)
	{
		free_ast(left);
		free_ast(right);
		return (NULL);
	}
	return (pipe_node);
}

/* Parse pipe sequence */
t_ast_node	*parse_pipe_sequence(t_token **token)
{
	t_ast_node	*left;

	if (!token || !*token)
		return (NULL);
	left = handle_pipe_left(token);
	if (!left)
		return (NULL);
	if (!*token || (*token)->type != TOKEN_PIPE)
		return (left);
	return (handle_pipe_right(token, left));
}
