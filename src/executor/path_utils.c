/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/30 22:36:21 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/13 10:20:26 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "common.h"
#include <sys/stat.h>

static int	append_path(char **joined, char *to_append, bool add_slash)
{
	char	*temp;
	char	*new_str;

	new_str = NULL;
	temp = *joined;
	if (add_slash)
	{
		new_str = ft_strjoin(temp, "/");
		if (!*joined)
			return (ERR_MALLOC);
		free(temp);
		*joined = new_str;
	}
	temp = *joined;
	new_str = ft_strjoin(temp, to_append);
	if (!new_str)
		return (free(temp), ERR_MALLOC);
	free(temp);
	*joined = new_str;
	return (0);
}

static int	validate_path_c(char *path, char *full_path)
{
	struct stat	info;

	if (access(path, F_OK) == -1)
		return (error(full_path, NULL), ERR_NO_FILE);
	if (stat(path, &info) == -1)
		return (error(full_path, NULL), ERR_ACCESS);
	if (!S_ISDIR(info.st_mode))
		return (error(full_path, NOT_DIR), ERR_NOT_DIR);
	return (0);
}

static int	validate_dir_c(char *full_path, char **paths, char **joined, int *i)
{
	int	status;

	if (*joined == NULL)
	{
		*joined = ft_strdup("");
		if (!*joined)
			return (ERR_MALLOC);
	}
	while (paths[(*i) + 1])
	{
		if ((*i) > 0 || full_path[0] == '/')
		{
			status = append_path(joined, "/", false);
			if (status != 0)
				return (status);
		}
		status = append_path(joined, paths[*i], false);
		if (status != 0)
			return (status);
		status = validate_path_c(*joined, full_path);
		if (status != 0)
			return (status);
		(*i)++;
	}
	return (0);
}

static int	validate_trailing_c(char *full_path, char **paths, \
			char **joined, int i)
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
	status = append_path(joined, paths[i], true);
	if (status != 0)
		return (status);
	return (validate_path_c(*joined, full_path));
}

int	validate_path(char *full_path)
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
	status_ = validate_dir_c(full_path, paths, &joined, &i);
	if (status_ != 0)
	{
		free(joined);
		return (free_tab(paths), status_);
	}
	status_ = validate_trailing_c(full_path, paths, &joined, i);
	free(joined);
	free_tab(paths);
	return (status_);
}
