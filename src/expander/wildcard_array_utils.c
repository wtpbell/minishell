/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard_array_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/20 19:32:41 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/13 10:20:53 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"
#include "common.h"

char	**init_matches_array(int initial_capacity)
{
	char	**matches;

	matches = malloc(sizeof(char *) * initial_capacity);
	return (matches);
}

int	should_include_file(const char *filename, const char *pattern)
{
	if (filename[0] == '.' && pattern[0] != '.')
		return (0);
	return (1);
}

char	**grow_matches_array(char **matches, int *capacity)
{
	int		new_capacity;
	char	**new_matches;

	new_capacity = (*capacity) * 2;
	new_matches = (char **)mem_realloc(matches, sizeof(char *) * new_capacity,
			sizeof(char *) * (*capacity));
	if (new_matches)
		*capacity = new_capacity;
	return (new_matches);
}

void	cleanup_matches(char **matches, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(matches[i]);
		i++;
	}
	free(matches);
}
