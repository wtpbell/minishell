/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:54:15 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/13 19:29:14 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Check if a token is a redirection operator */

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
	ft_memset(node, 0, sizeof(t_ast_node));
	node->type = type;
	node->args = NULL;
	node->argc = 0;
	node->redirections = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static int	copy_and_add_arg(char **new_args, char **old_args,
					char *arg, int args_len)
{
	int	i;

	i = 0;
	while (i < args_len)
	{
		new_args[i] = old_args[i];
		i++;
	}
	new_args[args_len] = ft_strdup(arg);
	if (!new_args[args_len])
	{
		free(new_args);
		return (0);
	}
	new_args[args_len + 1] = NULL;
	return (1);
}

/* Add an argument to the node */
void	add_arg_to_node(t_ast_node *node, char *arg)
{
	char	**new_args;
	int		args_len;
	int		i;

	i = 0;
	if (!node || !arg)
		return ;
	args_len = get_args_length(node->args);
	new_args = (char **)malloc(sizeof(char *) * (args_len + 2));
	if (!new_args)
		return ;
	if (!copy_and_add_arg(new_args, node->args, arg, args_len))
	{
		while (--i >= 0)
			free(new_args[i]);
		free(new_args);
		return ;
	}
	free(node->args);
	node->args = new_args;
	node->argc++;
}
