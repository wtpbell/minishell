/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipeline_handler.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:55:20 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/15 19:49:42 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*create_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*pipe_node;

	if (!left || !right)
	{
		if (left)
			free_ast(left);
		if (right)
			free_ast(right);
		return (NULL);
	}
	pipe_node = create_ast_node(TOKEN_PIPE);
	if (!pipe_node)
	{
		free_ast(left);
		free_ast(right);
		return (NULL);
	}
	pipe_node->left = left;
	pipe_node->right = right;
	return (pipe_node);
}

t_ast_node	*handle_redirection_in_pipe(t_ast_node *left,
											t_token **token)
{
	t_ast_node		*redir;
	int				i;
	t_quote_type	quote_type;

	redir = parse_redirection(token);
	if (!redir)
		return (free_ast(left), NULL);
	if (!redir->args || !redir->args[0])
	{
		if (left->args && left->args[0])
		{
			i = 0;
			while (left->args[i])
			{
				if (left->arg_quote_types)
					quote_type = left->arg_quote_types[i];
				else
					quote_type = QUOTE_NONE;
				add_arg_to_node(redir, left->args[i], quote_type);
				i++;
			}
		}
	}
	free_ast(left);
	return (redir);
}

static int	validate_pipeline_structure(t_ast_node *root)
{
	t_ast_node	*current;
	int			valid;

	if (!root)
		return (0);
	current = root;
	valid = 1;
	while (current && valid)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (!current->left || !current->right)
			{
				ft_putstr_fd(RED, STDERR_FILENO);
				ft_putendl_fd(
					"minishell: syntax error near unexpected token '|'",
					STDERR_FILENO);
				ft_putstr_fd(RESET, STDERR_FILENO);
				valid = 0;
				break ;
			}
		}
		current = current->right;
	}
	return (valid);
}

t_ast_node	*parse_pipeline(t_token **token)
{
	t_ast_node	*root;
	t_ast_node	*pipe_node;

	if (!token || !*token)
		return (NULL);
	root = parse_pipe_sequence(token);
	if (!root)
		return (NULL);
	while (*token && (*token)->type == TOKEN_PIPE)
	{
		pipe_node = handle_pipe_right(token, root);
		if (!pipe_node)
			return (NULL);
		root = pipe_node;
	}
	if (!validate_pipeline_structure(root))
	{
		free_ast(root);
		return (NULL);
	}
	return (root);
}
