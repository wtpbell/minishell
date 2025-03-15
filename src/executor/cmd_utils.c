/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 16:48:58 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/15 21:17:17 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "parser.h"
#include "common.h"
#include <sys/stat.h>

void	append_cwd(t_ast_node *node)
{
	char	cwd[PATH_MAX];
	char	*tmp;
	char	*tmp2;

	if (!getcwd(cwd, PATH_MAX))
		return (error("exec", "Failed to get CWD"));
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
	paths = mem_split(path_var, ":");
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i++], "/");
		full_path = ft_strjoin(tmp, cmd);
		if (access(full_path, F_OK) == 0)
			return (free_tab(paths), free(tmp), full_path);
		free(full_path);
		free(tmp);
	}
	return (free_tab(paths), NULL);
}

static int	resolve_command(t_ast_node *node)
{
	char	*tmp;

	tmp = get_cmd_path(node->args[0]);
	if (!tmp)
	{
		error(node->args[0], "command not found");
		set_underscore(node->argc, node->args);
		return (set_exit_status(127), 127);
	}
	free(node->args[0]);
	node->args[0] = tmp;
	return (0);
}

static int	resolve_path(t_ast_node *node)
{
	int			i;
	struct stat	info;

	i = validate_path(node->args[0]);
	if (i != 0)
		return (set_underscore(node->argc, node->args), set_exit_status(i), i);
	if (access(node->args[0], F_OK) == -1)
		return (set_underscore_error(node, NO_FILE_DIR, 127));
	if (stat(node->args[0], &info) == -1)
		return (error(node->args[0], NULL), 126);
	if (S_ISDIR(info.st_mode))
		return (set_underscore_error(node, IS_DIR, 126));
	if (access(node->args[0], R_OK | X_OK) == -1)
		return (set_underscore_error(node, PERMISSION_DENIED, 126));
	return (0);
}

int	check_cmd(t_ast_node *node, t_env **env)
{
	int		status_;
	bool	is_path_cmd;

	if (!node || !node->args || !node->args[0])
		return (set_exit_status(0), 0);
	is_path_cmd = (node->args[0][0] == '/' || node->args[0][0] == '.');
	if (get_env_value(*env, "PATH") == NULL && !is_path_cmd)
		append_cwd(node);
	if (is_path_cmd)
		status_ = resolve_path(node);
	else
		status_ = resolve_command(node);
	return (status_);
}
