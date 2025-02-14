/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_validator.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 10:18:14 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/14 15:09:51 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_cmd_valid_error	validate_node_args(t_ast_node *node)
{
	if (node->left && node->left->args && node->left->args[0])
	{
		if (!is_valid_command_name(node->left->args[0]))
			return (VALID_SYNTAX_ERROR);
		if (node->left->argc > 1024)
			return (VALID_TOO_MANY_ARGS);
	}
	else if (!node->args || !node->args[0])
	{
		if (!node->redirections)
			return (VALID_EMPTY_CMD);
	}
	return (VALID_SUCCESS);
}

static t_cmd_valid_error	validate_children(t_ast_node *node)
{
	t_cmd_valid_error	status;

	if (node->left)
	{
		status = validate_command_syntax(node->left);
		if (status != VALID_SUCCESS)
			return (status);
	}
	if (node->right)
	{
		status = validate_command_syntax(node->right);
		if (status != VALID_SUCCESS)
			return (status);
	}
	return (VALID_SUCCESS);
}

t_cmd_valid_error	validate_redirection_syntax(t_redir *redirs)
{
	t_redir	*curr;

	curr = redirs;
	while (curr)
	{
		if (!curr->file)
			return (VALID_MISSING_FILENAME);
		if (!is_valid_command_name(curr->file))
			return (VALID_INVALID_REDIR);
		curr = curr->next;
	}
	return (VALID_SUCCESS);
}

t_cmd_valid_error	validate_command_syntax(t_ast_node *node)
{
	t_cmd_valid_error	status;

	if (!node)
		return (VALID_EMPTY_CMD);
	if (node->redirections)
	{
		status = validate_redirection_syntax(node->redirections);
		if (status != VALID_SUCCESS)
			return (status);
	}
	if (node->type == TOKEN_WORD)
	{
		status = validate_node_args(node);
		if (status != VALID_SUCCESS)
			return (status);
	}
	return (validate_children(node));
}
