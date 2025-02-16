/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/30 22:36:21 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/16 20:40:17 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "common.h"
#include <sys/stat.h>

static int	last_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (str[i - 1]);
}

static int	check_leading_paths(char *full_path, char **paths, char **joined, int *i)
{
	struct stat info;

	if (*joined == NULL)
		*joined = mem_strdup("");
	while (paths[(*i)])
	{
		if (full_path[0] == '/')
		{
			*joined = mem_strdup(full_path);
			break ;
		}
		if ((*i) > 0 || full_path[0] == '/')
			*joined = mem_strjoin(*joined, "/");
		*joined = mem_strjoin(*joined, paths[*i]);
		if (access(*joined, F_OK) == -1) 
			return (error(full_path, "No such file or directory"), 127);
		if (stat(*joined, &info) == -1)
			return (error(full_path, NULL), 1);
		if (!S_ISDIR(info.st_mode))
			return (error(full_path, "Not a directory"), 126);
		(*i)++;
	}
	return (0);
}


int	check_last_path(char *full_path, char **paths, char **joined, int i)
{
	struct stat	info;

	if (last_char(full_path) == '/')
	{
		(*joined) = mem_strjoin((*joined), "/");
		(*joined) = mem_strjoin((*joined), paths[i]);
		if (access((*joined), F_OK) == -1)
			return (error(full_path, "No such file or directory"), 127);
		stat((*joined), &info);
		if (!S_ISDIR(info.st_mode))
			return (error(full_path, "Not a directory"), 126);
	}
	return (0);
}

int	check_paths(char *full_path)
{
	char	**paths;
	int		i;
	char	*joined;
	int		status_;

	if (full_path[0] == '/' && full_path[1] == '\0')
		return (0);
	paths = mem_split(full_path, "/");
	joined = NULL;
	i = 0;
	status_ = check_leading_paths(full_path, paths, &joined, &i);
	if (status_ != 0)
		return (status_);
	return (check_last_path(full_path, paths, &joined, i));
}
