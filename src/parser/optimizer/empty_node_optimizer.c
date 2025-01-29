/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   empty_node_optimizer.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/29 12:55:18 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/29 17:02:15 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_empty_string(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	is_empty_command(t_ast_node *node)
{
	if (!node->args || !node->args[0])
		return (1);
	if (is_empty_string(node->args[0]))
		return (1);
	return (0);
}

static t_ast_node	*handle_parentheses(t_ast_node *node)
{
	t_ast_node	*child;

	if (node->type != TOKEN_LPAREN && node->type != TOKEN_RPAREN)
		return (node);
	if (!node->left || node->right)
	{
		free_ast(node);
		return (NULL);
	}
	child = node->left;
	node->left = NULL;
	free_ast(node);
	return (child);
}

static t_ast_node	*optimize_empty_node(t_ast_node *node)
{
	if (!node)
		return (NULL);
	if (node->type == TOKEN_WORD && is_empty_command(node))
	{
		free_ast(node);
		return (NULL);
	}
	return (handle_parentheses(node));
}

t_ast_node	*remove_empty_nodes(t_ast_node *node)
{
	t_ast_node	*optimized;

	if (!node)
		return (NULL);
	node->left = remove_empty_nodes(node->left);
	node->right = remove_empty_nodes(node->right);
	optimized = optimize_empty_node(node);
	if (optimized != node)
		return (optimized);
	if (!node->left && !node->right
		&& (node->type == TOKEN_PIPE || node->type == TOKEN_AND
			|| node->type == TOKEN_OR))
	{
		free_ast(node);
		return (NULL);
	}
	return (node);
}
