/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast_optimizer.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 16:40:36 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/29 13:16:14 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast_node	*optimize_pipeline(t_ast_node *node)
{
	if (!node || node->type != TOKEN_PIPE)
		return (node);
	node->left = optimize_pipeline(node->left);
	node->right = optimize_pipeline(node->right);
	return (node);
}

t_ast_node	*optimize_ast(t_ast_node *root)
{
	if (!root)
		return (NULL);
	root = remove_empty_nodes(root);
	if (!root)
		return (NULL);
	if (root->type == TOKEN_WORD && root->redirections)
		root->redirections = merge_redirections(root->redirections);
	root->left = optimize_ast(root->left);
	root->right = optimize_ast(root->right);
	return (optimize_pipeline(root));
}
