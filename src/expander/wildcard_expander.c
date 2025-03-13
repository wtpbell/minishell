/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard_expander.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/20 22:06:07 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/13 18:45:10 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"
#include "common.h"

void	copy_args_range(char **dest, char **source, int range[2], int *dest_idx)
{
	int	i;

	i = range[0];
	while (i < range[1])
		dest[(*dest_idx)++] = source[i++];
}

void	copy_matches(char **dest, char **matches, int match_count,
			int *dest_idx)
{
	int	i;

	i = 0;
	while (i < match_count)
		dest[(*dest_idx)++] = matches[i++];
}

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

void	process_wildcard_arg(t_ast_node *node, int i)
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

static char *process_wildcard_wo_expand(t_ast_node *node, int idx)
{
	int		i;
	int		j;
	char	*result;
	char	*arg;

	arg = node->args[idx];
	result = (char *)ft_calloc(sizeof(char), ft_strlen(arg)+1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
			result[j++] = arg[i];
		i++;
	}
	return (result);
}


void	expand_wildcards(t_ast_node *node)
{
	int				i;
	t_quote_type	quote_type;

	i = 0;
	if (!node || !node->args)
		return ;
	while (i < node->argc && node->args[i])
	{
		if (has_wildcard(node->args[i]) == 1)
		{
			process_wildcard_arg(node, i);
			i++;
			continue ;
		}
		else if (is_mixed_quote_type(node->args[i]), )
		{
			
		}
		i++;
	}
}
