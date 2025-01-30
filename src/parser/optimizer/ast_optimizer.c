/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast_optimizer.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 16:40:36 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/30 10:00:49 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*optimize_ast(t_ast_node *root)
{
	if (!root)
		return (NULL);
	root = remove_empty_nodes(root);
	if (!root)
		return (NULL);
	if (root->type == TOKEN_WORD && root->redirections)
		root->redirections = merge_redirections(root->redirections);
	else if (root->type == TOKEN_PIPE)
		root = optimize_pipeline(root);
	root->left = optimize_ast(root->left);
	root->right = optimize_ast(root->right);
	return (root);
}
