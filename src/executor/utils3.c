/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/30 22:36:21 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/23 23:10:08 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "common.h"
#include <sys/stat.h>

static int	join_path(char **joined, char *to_append, bool add_slash)
{
	char	*temp;

	temp = *joined;
	if (add_slash)
	{
		*joined = mem_strjoin(temp, "/");
		if (!*joined)
			return (ERR_MALLOC);
	}
	temp = *joined;
	*joined = mem_strjoin(temp, to_append);
	if (!*joined)
	{
		free(temp);
		return (ERR_MALLOC);
	}
	return (0);
}

// Helper function to check if path exists and is a directory
static int	validate_path(char *path, char *full_path)
{
	struct stat	info;

	if (access(path, F_OK) == -1)
		return (error(full_path, "No such file or directory"), ERR_NO_FILE);
	if (stat(path, &info) == -1)
		return (error(full_path, NULL), ERR_ACCESS);
	if (!S_ISDIR(info.st_mode))
		return (error(full_path, "Not a directory"), ERR_NOT_DIR);
	return (0);
}

static int	check_prefix(char *full_path, char **paths, char **joined, int *i)
{
	int	status;

	if (*joined == NULL)
	{
		*joined = mem_strdup("");
		if (!*joined)
			return (ERR_MALLOC);
	}
	while (paths[(*i) + 1])
	{
		if ((*i) > 0 || full_path[0] == '/')
		{
			status = join_path(joined, "/", false);
			if (status != 0)
				return (status);
		}
		status = join_path(joined, paths[*i], false);
		if (status != 0)
			return (status);
		status = validate_path(*joined, full_path);
		if (status != 0)
			return (status);
		(*i)++;
	}
	return (0);
}

int	check_last_path(char *full_path, char **paths, char **joined, int i)
{
	int	status;
	int	len;

	if (!full_path || full_path[0] == '\0')
		return (0);
	len = 0;
	while (full_path[len])
		len++;
	if (full_path[len - 1] != '/')
		return (0);
	status = join_path(joined, paths[i], true);
	if (status != 0)
		return (status);
	return (validate_path(*joined, full_path));
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
	if (!paths)
		return (-1);
	joined = NULL;
	i = 0;
	status_ = check_prefix(full_path, paths, &joined, &i);
	if (status_ != 0)
		return (status_);
	return (check_last_path(full_path, paths, &joined, i));
}
