/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 15:14:16 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/12 12:03:23 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "common.h"
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
/*
	Command				Expected Behavior
	cd dir1				Changes to dir1.
	cd nonexistent_dir	Prints "cd: nonexistent_dir: No such file or dir".
	cd					Goes to the home dir.
	cd ~				Goes to the home dir.
	cd ""				Prints "cd: invalid dir".
	cd dir1 dir2		Prints "cd: too many arguments".
	cd /path/to/file	Fails if /path/to/file is not a dir.
	cd ..				Goes to the parent dir.
*/

static void	update_pwd(t_env *envs, char *old_pwd, char *pwd)
{
	if (get_env_value(envs, "OLDPWD") == NULL)
		set_env(envs, "OLDPWD", "");
	set_env(envs, "OLDPWD", old_pwd);
	set_env(envs, "PWD", pwd);
}

static int	change_dir(t_ast_node *node, t_env **env, char *old_pwd)
{
	if (chdir(node->args[1]) == -1)
		return (error("cd", NULL), ERR_CHDIR);
	update_pwd(*env, old_pwd, node->args[1]);
	return (EXIT_SUCCESS);
}

static int	home_dir(t_env **env, bool home, char *old_pwd)
{
	char	*path;
	char	current_pwd[PATH_MAX];

	if (home)
		path = get_env_value(*env, "HOME");
	else
		path = get_env_value (*env, "OLDPWD");
	if (!path)
	{
		if (home)
			return (error("cd", "HOME is not set"), ERR_ENV);
		else
			return (error("cd", "OLDPWD is not set"), ERR_ENV);
	}
	if (chdir(path) == -1)
		return (error("cd", NULL), ERR_CHDIR);
	if (!home)
		ft_putendl_fd(path, STDOUT_FILENO);
	if (getcwd(current_pwd, PATH_MAX) != NULL)
		update_pwd(*env, old_pwd, current_pwd);
	return (EXIT_SUCCESS);
}

/*
	int stat(const char *path, struct stat *buf);
	- path:the path to the file or dir you want to query.
	- buf:  where the file's information will be stored.
	0: Success. The struct stat pointed to by buf is filled with the file's info.
	-1: Failure. The global variable errno is set to indicate the error
*/
int	builtin_cd(t_ast_node *node, t_env **env, t_token *tokens)
{
	char		old_pwd[PATH_MAX];
	int			status_;
	struct stat	info;

	(void) tokens;
	if (getcwd (old_pwd, PATH_MAX) == NULL)
		return (error("cd", NULL), EXIT_FAILURE);
	if (node->argc > 2)
		return (ft_putendl_fd(MANY_ARGS_ERROR, STDERR_FILENO), EXIT_FAILURE);
	if (node->argc == 1 || ft_strcmp(node->args[1], "~") == 0)
		return (home_dir(env, true, old_pwd));
	if (ft_strcmp(node->args[1], "-") == 0)
		return (home_dir(env, false, old_pwd));
	if (node->argc == 2 && ft_strcmp(node->args[1], "") == 0)
		return (set_exit_status(0), 0);
	if (stat(node->args[1], &info) == -1)
		return (error("cd", NO_FILE_DIR), EXIT_FAILURE);
	if (!S_ISDIR(info.st_mode))
		return (error("cd", NOT_DIR), EXIT_FAILURE);
	if (access(node->args[1], R_OK | X_OK) == -1)
		return (error("cd", PERMISSION_DENIED), EXIT_FAILURE);
	status_ = change_dir(node, env, old_pwd);
	if (status_ == EXIT_SUCCESS)
		set_underscore(node->argc, node->args);
	return (status_);
}
