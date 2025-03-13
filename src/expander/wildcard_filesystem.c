/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard_filesystem.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/26 14:14:19 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/13 10:21:20 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"
#include "common.h"

int	add_matching_file(char ***matches, int *count, int *capacity,
			const char *filename)
{
	char	**new_matches;

	if (*count >= *capacity)
	{
		new_matches = grow_matches_array(*matches, capacity);
		if (!new_matches)
			return (0);
		*matches = new_matches;
	}
	(*matches)[*count] = ft_strdup(filename);
	if (!(*matches)[*count])
		return (0);
	(*count)++;
	return (1);
}

int	process_dir_entries(DIR *dir, t_dir_info *info)
{
	struct dirent	*entry;

	entry = readdir(dir);
	while (entry)
	{
		if (should_include_file(entry->d_name, info->pattern)
			&& match_pattern(info->pattern, entry->d_name))
		{
			if (!add_matching_file(info->matches, info->count,
					info->capacity, entry->d_name))
				return (0);
		}
		entry = readdir(dir);
	}
	return (1);
}

char	**get_matching_files(const char *pattern, int *num_matches)
{
	DIR			*dir;
	char		**matches;
	int			count;
	int			capacity;
	t_dir_info	info;

	matches = NULL;
	count = 0;
	capacity = 10;
	*num_matches = 0;
	if (!pattern)
		return (NULL);
	matches = init_matches_array(capacity);
	if (!matches)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (free(matches), NULL);
	info = (t_dir_info){&matches, &count, &capacity, (char *)pattern};
	if (!process_dir_entries(dir, &info))
		return (cleanup_matches(matches, count), closedir(dir), NULL);
	closedir(dir);
	*num_matches = count;
	return (matches);
}

void	expand_redir_wildcards(t_redir *redir)
{
	int		match_count;
	char	**matches;

	while (redir)
	{
		if (redir->file && has_wildcard(redir->file))
		{
			matches = get_matching_files(redir->file, &match_count);
			if (matches && match_count > 0)
			{
				if (match_count > 1)
				{
					error(redir->file, "ambiguous redirect");
					free_matches(matches, match_count);
					set_exit_status(1);
					return ;
				}
				free(redir->file);
				redir->file = ft_strdup(matches[0]);
			}
			free_matches(matches, match_count);
		}
		redir = redir->next;
	}
}
