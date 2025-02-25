/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:54:15 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/25 16:31:44 by spyun         ########   odam.nl         */
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
	ft_memset(node, 0, sizeof(t_ast_node));
	node->type = type;
	node->args = NULL;
	node->arg_quote_types = NULL;
	node->argc = 0;
	node->redirections = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

// static int	copy_and_add_arg(char **new_args, char **old_args,
// 					char *arg, int args_len)
// {
// 	int	i;

// 	i = 0;
// 	while (i < args_len)
// 	{
// 		new_args[i] = old_args[i];
// 		i++;
// 	}
// 	new_args[args_len] = ft_strdup(arg);
// 	if (!new_args[args_len])
// 	{
// 		free(new_args);
// 		return (0);
// 	}
// 	new_args[args_len + 1] = NULL;
// 	return (1);
// }

/* Add an argument to the node */
void	add_arg_to_node(t_ast_node *node, char *arg, t_quote_type quote_type)
{
	char		**new_args;
	t_quote_type	*new_quote_types;
	int		args_len;
	int		i;

	if (!node || !arg)
		return ;
	args_len = get_args_length(node->args);
	new_args = (char **)malloc(sizeof(char *) * (args_len + 2));
	if (!new_args)
		return ;
	new_quote_types = (t_quote_type *)malloc(sizeof(t_quote_type) * (args_len + 2));
	if (!new_quote_types)
	{
		free(new_args);
		return ;
	}
	i = 0;
	while (i < args_len)
	{
		new_args[i] = node->args[i];
		new_quote_types[i] = node->arg_quote_types ? node->arg_quote_types[i] : QUOTE_NONE;
		i++;
	}
	new_args[args_len] = ft_strdup(arg);
	new_quote_types[args_len] = quote_type;
	new_args[args_len + 1] = NULL;
	new_quote_types[args_len + 1] = QUOTE_NONE;
	free(node->args);
	free(node->arg_quote_types);
	node->args = new_args;
	node->arg_quote_types = new_quote_types;
	node->argc++;
}
