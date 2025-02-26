/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_wildcard_utils.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/20 19:32:41 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/26 13:22:01 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"
#include "common.h"

/* Initialize matches array for wildcard expansion */
static char	**init_matches_array(int initial_capacity)
{
	char **matches;

	matches = mem_alloc(sizeof(char *) * initial_capacity);
	return (matches);
}

/* Check if a filename should be included based on hidden file rules */
static int	should_include_file(const char *filename, const char *pattern)
{
	if (filename[0] == '.' && pattern[0] != '.')
		return (0);
	return (1);
}

/* Grow matches array when needed */
static char	**grow_matches_array(char **matches, int *capacity)
{
	int		new_capacity;
	char	**new_matches;

	new_capacity = (*capacity) * 2;
	new_matches = realloc(matches, sizeof(char *) * new_capacity);
	if (new_matches)
		*capacity = new_capacity;
	return (new_matches);
}

/* Clean up matches if allocation fails */
static void	cleanup_matches(char **matches, int count)
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

// static int match_patterns(char *pattern, char *string)
// {
// 	char	*p;
// 	char	*s;
// 	char	*star;
// 	char	*ss;

// 	p = pattern;
// 	s = string;
// 	star = NULL;
// 	ss = NULL;
// 	while (*s)
// 	{
// 		if (*p == *s || *p == '?')
// 		{
// 			p++;
// 			s++;
// 		}
// 		else if (*p == '*')
// 		{
// 			star = p++;
// 			ss = s;
// 		}
// 		else if (star)
// 		{
// 			p = star + 1;
// 			s = ++ss;
// 		}
// 		else
// 			return (0);
// 	}
// 	while (*p == '*')
// 		p++;
// 	return (*p == '\0');
// }


/* Get files matching a wildcard pattern */
char	**get_matching_files(const char *pattern, int *num_matches)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	int				count;
	int				capacity;
	char			**new_matches;

	matches = NULL;
	count = 0;
	capacity = 10;
	*num_matches = 0;
	if (!pattern)
		return ((NULL));
	matches = init_matches_array(capacity);
	if (!matches)
		return (NULL);
	dir = opendir(".");
	if (!dir)
	{
		free(matches);
		return (NULL);
	}
	entry = readdir(dir);
	while (entry != (NULL))
	{
	if (should_include_file(entry->d_name, pattern) &&
		match_pattern(pattern, entry->d_name))
		{
		if (count >= capacity)
		{
			new_matches = grow_matches_array(matches, &capacity);
			if (!new_matches)
			{
					cleanup_matches(matches, count);
					closedir(dir);
					return (NULL);
			}
			matches = new_matches;
			}
			matches[count] = mem_strdup(entry->d_name);
			if (!matches[count])
			{
				cleanup_matches(matches, count);
				closedir(dir);
				return (NULL);
			}
			count++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	*num_matches = count;
	return matches;
}

