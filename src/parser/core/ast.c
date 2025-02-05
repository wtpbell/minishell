/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:54:15 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/05 09:26:33 by spyun         ########   odam.nl         */
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

void	add_arg_to_node(t_ast_node *node, char *arg)
{
	char	**new_args;
	int		args_len;

	if (!node || !arg)
		return ;
	args_len = get_args_length(node->args);
	new_args = (char **)malloc(sizeof(char *) * (args_len + 2));
	if (!new_args)
		return ;
	if (node->args)
	{
		while (args_len--)
			new_args[args_len] = node->args[args_len];
		free(node->args);
	}
	new_args[node->argc] = ft_strdup(arg);
	new_args[node->argc + 1] = NULL;
	if (!new_args[node->argc])
	{
		free(new_args);
		return ;
	}
	node->args = new_args;
	node->argc++;
}
