/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard_array_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/20 19:32:41 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/03 11:51:38 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"
#include "common.h"

/* Initialize matches array for wildcard expansion */
char	**init_matches_array(int initial_capacity)
{
	char	**matches;

	matches = mem_alloc(sizeof(char *) * initial_capacity);
	return (matches);
}

/* Check if a filename should be included based on hidden file rules */
int	should_include_file(const char *filename, const char *pattern)
{
	if (filename[0] == '.' && pattern[0] != '.')
		return (0);
	return (1);
}

/* Grow matches array when needed */
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

/* Clean up matches if allocation fails */
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
