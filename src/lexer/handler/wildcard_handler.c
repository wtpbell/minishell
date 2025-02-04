/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard_handler.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/30 11:15:13 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/03 14:45:28 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int	match_pattern(const char *pattern, const char *str)
{
	if (*pattern == '\0' && *str == '\0')
		return (1);
	if (*pattern == '*' && *(pattern + 1) != '\0' && *str == '\0')
		return (0);
	if (*pattern == '*')
		return (match_pattern(pattern + 1, str)
			|| (*str != '\0' && match_pattern(pattern, str + 1)));
	if (*pattern == *str)
		return (*str != '\0' && match_pattern(pattern + 1, str + 1));
	return (0);
}

static int	count_matches(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	dir = opendir(".");
	if (!dir)
		return (0);
	count = 0;
	entry = readdir(dir);
	while ((entry != NULL))
	{
		if (entry->d_name[0] != '.' && match_pattern(pattern, entry->d_name))
			count++;
	}
	closedir(dir);
	return (count);
}

static char	**get_matches(const char *pattern, int count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	int				i;

	matches = (char **)malloc(sizeof(char *) * (count + 1));
	if (!matches)
		return (NULL);
	dir = opendir(".");
	if (!dir)
	{
		free(matches);
		return (NULL);
	}
	i = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.' && match_pattern(pattern, entry->d_name))
			matches[i++] = ft_strdup(entry->d_name);
	}
	matches[i] = NULL;
	closedir(dir);
	return (matches);
}

char	**expand_wildcards(const char *pattern)
{
	int		count;
	char	**matches;

	if (!pattern || !ft_strchr(pattern, '*'))
	{
		matches = (char **)malloc(sizeof(char *) * 2);
		if (!matches)
			return (NULL);
		matches[0] = ft_strdup(pattern);
		matches[1] = NULL;
		return (matches);
	}
	count = count_matches(pattern);
	if (count == 0)
	{
		matches = (char **)malloc(sizeof(char *) * 2);
		if (!matches)
			return (NULL);
		matches[0] = ft_strdup(pattern);
		matches[1] = NULL;
		return (matches);
	}
	return (get_matches(pattern, count));
}
