/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard_replacement.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/26 13:48:45 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/26 14:38:06 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"
#include "common.h"

/* Calculate new arguments count and prepare for replacement */
static int	prepare_replacement(t_ast_node *node, int arg_idx, int match_count,
			int *new_argc)
{
	(void)arg_idx;
	*new_argc = node->argc + match_count - 1;
	return (1);
}

/* Handle allocation of new arguments array */
static char	**allocate_replacement_args(int size)
{
	char	**new_args;

	new_args = mem_alloc(sizeof(char *) * (size + 1));
	if (new_args)
		new_args[size] = NULL;
	return (new_args);
}

/* Update node with new arguments */
static void	update_node_args(t_ast_node *node, char **new_args, char **old_args,
			int new_argc)
{
	node->args = new_args;
	node->argc = new_argc;
	free(old_args);
}

/* Handles the replacement of a wildcard argument with its matches */
bool	replace_wildcard_arg(t_ast_node *node, int arg_idx, char **matches,
		int match_count)
{
	int		new_argc;
	char	**new_args;
	int		dest_idx;
	char	**old_args;
	int range1[2] = {0, arg_idx};
	int range2[2] = {arg_idx + 1, node->argc};

	if (!prepare_replacement(node, arg_idx, match_count, &new_argc))
		return (false);
	new_args = allocate_replacement_args(new_argc);
	if (!new_args)
	{
		free_matches(matches, match_count);
		return (false);
	}
	dest_idx = 0;
	copy_args_range(new_args, node->args, range1, &dest_idx);
	copy_matches(new_args, matches, match_count, &dest_idx);
	copy_args_range(new_args, node->args, range2, &dest_idx);
	free(node->args[arg_idx]);
	free(matches);
	old_args = node->args;
	update_node_args(node, new_args, old_args, new_argc);
	return (true);
}
