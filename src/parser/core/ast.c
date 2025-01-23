/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:54:15 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/23 17:30:16 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Create and initialise AST nodes */
t_ast_node	*create_ast_node(t_token_type type)
{
	t_ast_node	*node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->redirections = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

/*
** Add command arguments to the AST node
** Replace the existing argument array with an array containing the new arguments
*/
void	add_arg_to_node(t_ast_node *node, char *arg)
{
	char	**new_args;
	int		i;
	int		len;

	if (!node || !arg)
		return ;
	len = 0;
	if (node->args)
	{
		while (node->args[len])
			len++;
	}
	new_args = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_args)
		return ;
	i = 0;
	while (i < len)
	{
		new_args[i] = node->args[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	free(node->args);
	node->args = new_args;
}
