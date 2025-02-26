/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_wildcard.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/20 22:06:07 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/20 22:16:51 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"
#include "common.h"

// Allocates and initializes new arguments array
static char	**allocate_new_args(int size)
{
	char	**new_args;

	new_args = malloc(sizeof(char*) * (size + 1));
	if (new_args)
		new_args[size] = NULL;
	return (new_args);
}

// Copies arguments from source to destination within specified range
static void	copy_args_range(char **dest, char **source, int start, int end, int *dest_idx)
{
	int	i;

	i = start;
	while (i < end)
		dest[(*dest_idx)++] = source[i++];
}

// Copies matches into the destination array
static void	copy_matches(char **dest, char **matches, int match_count, int *dest_idx)
{
	int	i;

	i = 0;
	while (i < match_count)
		dest[(*dest_idx)++] = matches[i++];
}

// Frees matches array and its contents
static void	free_matches(char **matches, int match_count)
{
	int	i;

	i = 0;
	if (!matches)
		return ;
	while (i < match_count)
		free(matches[i++]);
	free(matches);
}

// Handles the replacement of a wildcard argument with its matches
static bool	replace_wildcard_arg(t_ast_node *node, int arg_idx, char **matches, int match_count)
{
	int		new_argc;
	char	**new_args;
	int		dest_idx;
	char	**old_args;

	new_argc = node->argc + match_count - 1;
	new_args = allocate_new_args(new_argc);
	if (!new_args)
	{
	free_matches(matches, match_count);
	return false;
	}
	dest_idx = 0;
	copy_args_range(new_args, node->args, 0, arg_idx, &dest_idx);
	copy_matches(new_args, matches, match_count, &dest_idx);
	copy_args_range(new_args, node->args, arg_idx + 1, node->argc, &dest_idx);
	free(node->args[arg_idx]);
	free(matches);
	old_args = node->args;
	node->args = new_args;
	node->argc = new_argc;
	free(old_args);
	return (true);
}

// Main function that expands wildcards in command arguments
void	expand_wildcards(t_ast_node *node)
{
	int	i;
	int	match_count;
	char **matches;

	i = 0;
	if (!node || !node->args)
		return ;
	while (i < node->argc && node->args[i])
	{
		if (i > 0 && has_wildcard(node->args[i]))
		{
			match_count = 0;
			matches = get_matching_files(node->args[i], &match_count);
			if (matches && match_count > 0)
			{
				if (!replace_wildcard_arg(node, i, matches, match_count))
				{
					i++;
					continue ;
				}
				continue ;
			}
			else if (matches)
				free(matches);
		}
		i++;
	}
}
