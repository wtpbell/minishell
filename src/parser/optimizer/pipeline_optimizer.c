/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipeline_optimizer.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/29 15:39:22 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/29 17:00:00 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Check if the command is empty */
static int	is_empty_command(t_ast_node *node)
{
	if (!node || node->type != TOKEN_WORD)
		return (1);
	if (!node->args || !node->args[0])
		return (1);
	return (0);
}

/* Remove empty pipe segment */
static t_ast_node	*remove_empty_pipe_segment(t_ast_node *node)
{
	t_ast_node	*result;

	if (!node)
		return (NULL);
	if (node->type != TOKEN_PIPE)
		return (node);
	if (is_empty_command(node->left))
		result = node->right;
	else if (is_empty_command(node->right))
		result = node->left;
	else
		return (node);
	node->left = NULL;
	node->right = NULL;
	free_ast(node);
	return (result);
}

static t_ast_node	*merge_consecutive_pipes(t_ast_node *node)
{
	t_ast_node	*curr;
	t_ast_node	*next;

	if (!node || node->type != TOKEN_PIPE)
		return (node);
	curr = node;
	while (curr && curr->type == TOKEN_PIPE)
	{
		next = curr->right;
		if (next && next->type == TOKEN_PIPE)
		{
			curr->right = next->right;
			next->right = NULL;
			free_ast(next);
		}
		else
			curr = curr->right;
	}
	return (node);
}

/* Optimize pipeline */
t_ast_node	*optimize_pipeline(t_ast_node *node)
{
	if (!node)
		return (NULL);
	if (node->type != TOKEN_PIPE)
	{
		node->left = optimize_pipeline(node->left);
		node->right = optimize_pipeline(node->right);
		return (node);
	}
	node->left = optimize_pipeline(node->left);
	node->right = optimize_pipeline(node->right);
	node = remove_empty_pipe_segment(node);
	if (node && node->type == TOKEN_PIPE)
		node = merge_consecutive_pipes(node);
	return (node);
}
