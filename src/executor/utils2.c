/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 16:48:58 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/04 09:35:42 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "parser.h"
#include <sys/stat.h>

void	append_cwd(t_ast_node *node)
{
	char	cwd[PATH_MAX];
	char	*tmp;
	char	*tmp2;

	getcwd(cwd, PATH_MAX);
	tmp = ft_strjoin(cwd, "/");
	tmp2 = ft_strjoin(tmp, node->args[0]);
	free(tmp);
	free(node->args[0]);
	node->args[0] = tmp2;
}

char	*get_cmd_path(char *cmd)
{
	char	*path_var;
	char	**paths;
	char	*full_path;
	char	*tmp;
	size_t	i;

	if (ft_strcmp(cmd, "") == 0)
		return (NULL);
	path_var = get_env_value(*get_env_list(), "PATH");
	if (!path_var)
		return (NULL);
	paths = ft_split_mini(path_var, ":");
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		if (access(full_path, F_OK) == 0)
			return (free(paths), free(tmp), full_path); //i need to free paths tab 
		free(full_path);//i need to free full_path tab
		free(tmp);
		i++;
	}
	return (free(paths), NULL);
}

int	exec_path(t_ast_node *node)
{
	char	*tmp;

	tmp = get_cmd_path(node->args[0]);
	// printf("print tmp: %s\n", tmp);
	if (!tmp)
	{
		error(node->args[0], "Command not found");
		set_underscore(node->argc, node->args);
		return (set_exit_status(127), 127);
	}
	free(node->args[0]);
	node->args[0] = tmp;
	return (0);
}

int	exec_exec(t_ast_node *node)
{
	int			i;
	struct stat	info;

	i = check_paths(node->args[0]);
	if (i != 0)
		return (set_underscore(node->argc, node->args), set_exit_status(i), i);
	if (access(node->args[0], F_OK) == -1)
	{
		error(node->args[0], "No such file or directory");
		return (set_exit_status(127), 127);
	}
	if (stat(node->args[0], &info) == -1)
		return (error(node->args[0], NULL), 1);
	if (!S_ISDIR(info.st_mode))
	{
		error(node->args[0], "Is not a directory");
		return (set_exit_status(126), 126);
	}
	if (access(node->args[0], R_OK | X_OK) == -1)
	{
		error(node->args[0], "Permission denied");
		return (set_exit_status(126), 126);
	}
	return (0);
}
/*
	check_cmd() handles cmd resolution
	1. No PATH and not an absolute/relative command
	2. Not an absolute/relative
	3. Absolute/relative path
*/

int	check_cmd(t_ast_node *node)
{
	int status_;

	status_ = 0;
	if (get_env_value(*node->env, "PATH") == NULL && node->args[0][0] != '/'
			&& node->args[0][0] != '.')
		append_cwd(node);
	if (node->args[0][0] != '/' && node->args[0][0] != '.')
		status_ = exec_path(node);
	else
		status_ = exec_exec(node);
	return (status_);
}

