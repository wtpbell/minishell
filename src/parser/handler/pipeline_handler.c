/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipeline_handler.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:55:20 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/05 15:07:18 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Check for pipe (|) token */
static int	is_pipe_token(t_token *token)
{
	if (!token || !token->content)
		return (0);
	return (token && token->type == TOKEN_PIPE);
}

/* Handling pipe syntax errors */
static t_ast_node	*handle_pipe_error(void)
{
	ft_putendl_fd("minishell: syntax error near unexpected token '|'",
		STDERR_FILENO);
	return (NULL);
}

/* Create a pipe node */
static t_ast_node	*create_pipe_node(t_token **token)
{
	t_ast_node	*node;

	if (!token || !*token || !is_pipe_token(*token))
		return (NULL);
	node = create_ast_node(TOKEN_PIPE);
	if (!node)
		return (NULL);
	*token = (*token)->next;
	if (!*token)
	{
		free_ast(node);
		return (handle_pipe_error());
	}
	return (node);
}

/* Parsing consecutive pipe commands */
static t_ast_node	*parse_pipe_sequence(t_token **token)
{
	t_ast_node	*left;
	t_ast_node	*pipe_node;
	t_ast_node	*right;

	if (!token || !*token)
		return (NULL);
	left = parse_command(token);
	if (!left || !*token || !is_pipe_token(*token))
		return (left);
	pipe_node = create_pipe_node(token);
	if (!pipe_node)
	{
		free_ast(left);
		return (NULL);
	}
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

/* Parsing the entire pipeline */
t_ast_node	*parse_pipeline(t_token **token)
{
	t_ast_node	*node;

	if (!token || !*token)
		return (NULL);
	node = parse_pipe_sequence(token);
	if (!node)
		return (NULL);
	if (is_pipe_token(*token))
		return (handle_pipe_error());
	return (node);
}
