/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard_expander.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/20 22:06:07 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/27 10:43:34 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"
#include "common.h"

/* Copies arguments from source to destination within specified range */
void	copy_args_range(char **dest, char **source, int range[2], int *dest_idx)
{
	int	i;

	i = range[0];
	while (i < range[1])
		dest[(*dest_idx)++] = source[i++];
}

/* Copies matches into the destination array */
void	copy_matches(char **dest, char **matches, int match_count,
			int *dest_idx)
{
	int	i;

	i = 0;
	while (i < match_count)
		dest[(*dest_idx)++] = matches[i++];
}

/* Frees matches array and its contents */
void	free_matches(char **matches, int match_count)
{
	int	i;

	i = 0;
	if (!matches)
		return ;
	while (i < match_count)
		free(matches[i++]);
	free(matches);
}

static void	process_wildcard_arg(t_ast_node *node, int i)
{
	int		match_count;
	char	**matches;

	match_count = 0;
	matches = get_matching_files(node->args[i], &match_count);
	if (matches && match_count > 0)
	{
		if (!replace_wildcard_arg(node, i, matches, match_count))
		{
			free_matches(matches, match_count);
			return ;
		}
	}
	else if (matches)
		free(matches);
}

/* Main function that expands wildcards in command arguments */
void	expand_wildcards(t_ast_node *node)
{
	int	i;

	i = 0;
	if (!node || !node->args)
		return ;
	while (i < node->argc && node->args[i])
	{
		if (has_wildcard(node->args[i]))
		{
			process_wildcard_arg(node, i);
			i++;
			continue ;
		}
		i++;
	}
}
