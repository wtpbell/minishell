/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:54:15 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/27 09:22:36 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Get the length of the argument array */
static int	get_args_length(char **args)
{
	int	len;

	len = 0;
	if (args)
	{
		while (args[len])
			len++;
	}
	return (len);
}

/* Create and initialise AST nodes */
t_ast_node	*create_ast_node(t_token_type type)
{
	t_ast_node	*node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->argc = 0;
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
	len = get_args_length(node->args);
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
	node->argc++;
}
