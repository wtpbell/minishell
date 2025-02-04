/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:54:15 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/03 15:03:47 by spyun         ########   odam.nl         */
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

static char	**expand_args_array(char **old_args, int old_len, int add_len)
{
	char	**new_args;
	int		i;

	new_args = (char **)malloc(sizeof(char *) * (old_len + add_len + 1));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < old_len)
	{
		new_args[i] = old_args[i];
		i++;
	}
	while (i <= old_len + add_len)
	{
		new_args[i] = NULL;
		i++;
	}
	return (new_args);
}

static void	copy_expanded_args(char **new_args, char **expanded_args,
	int old_len, int exp_len)
{
	int	i;

	i = 0;
	while (i < exp_len)
	{
		new_args[old_len + i] = expanded_args[i];
		i++;
	}
	new_args[old_len + i] = NULL;
}

void	add_arg_to_node(t_ast_node *node, char *arg)
{
	char	**expanded_args;
	char	**new_args;
	int		old_len;
	int		exp_len;

	if (!node || !arg)
		return ;
	expanded_args = expand_wildcards(arg);
	if (!expanded_args)
		return ;
	old_len = get_args_length(node->args);
	exp_len = get_args_length(expanded_args);
	new_args = expand_args_array(node->args, old_len, exp_len);
	if (!new_args)
		return ;
	copy_expanded_args(new_args, expanded_args, old_len, exp_len);
	free(expanded_args);
	free(node->args);
	node->args = new_args;
	node->argc = old_len + exp_len;
}
