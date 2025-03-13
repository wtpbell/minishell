/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard_replacement.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/26 13:48:45 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/13 10:21:41 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"
#include "common.h"

static int	prepare_replacement(t_ast_node *node, int match_count,
			int *new_argc)
{
	*new_argc = node->argc + match_count - 1;
	return (1);
}

static char	**allocate_replacement_args(int size)
{
	char	**new_args;

	new_args = malloc(sizeof(char *) * (size + 1));
	if (new_args)
		new_args[size] = NULL;
	return (new_args);
}

static void	update_node_args(t_ast_node *node, char **new_args, char **old_args,
			int new_argc)
{
	node->args = new_args;
	node->argc = new_argc;
	free(old_args);
}

static void	perform_copy_operations(t_copy_params params)
{
	int	dest_idx;
	int	ranges[2][2];

	ranges[0][0] = 0;
	ranges[0][1] = params.arg_idx;
	ranges[1][0] = params.arg_idx + 1;
	ranges[1][1] = params.node_argc;
	dest_idx = 0;
	copy_args_range(params.new_args, params.node_args, ranges[0], &dest_idx);
	copy_matches(params.new_args, params.matches,
		params.match_count, &dest_idx);
	copy_args_range(params.new_args, params.node_args, ranges[1], &dest_idx);
}

bool	replace_wildcard_arg(t_ast_node *node, int arg_idx, char **matches,
		int match_count)
{
	int				new_argc;
	char			**new_args;
	char			**old_args;
	t_copy_params	params;

	if (!prepare_replacement(node, match_count, &new_argc))
		return (false);
	new_args = allocate_replacement_args(new_argc);
	if (!new_args)
		return (free_matches(matches, match_count), false);
	params.new_args = new_args;
	params.node_args = node->args;
	params.arg_idx = arg_idx;
	params.matches = matches;
	params.match_count = match_count;
	params.node_argc = node->argc;
	perform_copy_operations(params);
	free(node->args[arg_idx]);
	free(matches);
	old_args = node->args;
	update_node_args(node, new_args, old_args, new_argc);
	return (true);
}
