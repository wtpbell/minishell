/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 13:02:50 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/21 08:55:30 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	return (parse_pipeline(&tokens));
}

void	free_ast(t_ast_node *node)
{
	int	i;

	if (!node)
		return ;
	if (node->args)
	{
		i = 0;
		while (node->args[i])
			free(node->args[i++]);
		free(node->args);
	}
	if (node->redirections)
		free(node->redirections);
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}
