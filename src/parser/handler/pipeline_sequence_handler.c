/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipeline_sequence_handler.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 11:14:04 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/06 14:02:12 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast_node	*handle_pipe_left(t_token **token)
{
	t_ast_node	*left;
	t_ast_node	*redir;

	if ((*token)->type != TOKEN_WORD && (*token)->type != TOKEN_WILDCARD)
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

static t_ast_node	*process_pipe_right_command(t_token **token)
{
	t_ast_node	*cmd_node;
	t_token		*current;

	current = *token;
	cmd_node = NULL;
	if (current && (is_redirection(current) || current->type == TOKEN_WORD))
	{
		cmd_node = handle_pipe_redirection(token);
		if (!cmd_node)
			return (NULL);
		return (cmd_node);
	}
	return (parse_pipe_sequence(token));
}

static t_ast_node	*handle_pipe_right(t_token **token, t_ast_node *left)
{
	t_ast_node	*right;
	t_ast_node	*pipe_node;

	if (!token || !*token)
		return (free_ast(left), NULL);
	*token = (*token)->next;
	right = process_pipe_right_command(token);
	if (!right)
		return (free_ast(left), NULL);
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
	if (is_redirection(*token))
	{
		left = handle_pipe_redirection(token);
		if (!left)
			return (NULL);
	}
	else if ((*token)->type == TOKEN_WORD)
	{
		left = handle_pipe_left(token);
		if (!left)
			return (NULL);
	}
	else
		return (NULL);
	if (!*token || (*token)->type != TOKEN_PIPE)
		return (left);
	return (handle_pipe_right(token, left));
}
