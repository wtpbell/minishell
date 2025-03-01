/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 15:14:16 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/01 09:49:02 by spyun         ########   odam.nl         */
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

static int	handle_home_dir(t_env **env)
{
	char	*home_path;

	home_path = get_env_value(*env, "HOME");
	if (!home_path)
		return (error("cd", "HOME not set"), ERR_ENV);
	if (chdir(home_path) == -1)
		return (error("cd", NULL), ERR_CHDIR);
	return (EXIT_SUCCESS);
}

static int	handle_prev_dir(t_env **env)
{
	char	*old_pwd;
	char	*prev_path;

	old_pwd = get_env_value(*env, "OLDPWD");
	if (!old_pwd)
		return (error("cd", "OLDPWD not set"), ERR_ENV);
	prev_path = mem_strdup(old_pwd);
	if (!prev_path)
		return (error("cd", "malloc failed"), ERR_MALLOC);
	if (chdir(prev_path) == -1)
	{
		free(prev_path);
		return (error("cd", NULL), ERR_CHDIR);
	}
	ft_putendl_fd(prev_path, STDOUT_FILENO);
	free(prev_path);
	return (EXIT_SUCCESS);
}

static int	cd_dir(t_ast_node *node, t_env **env)
{
	char	old_pwd[PATH_MAX];
	int		status;

	if (getcwd(old_pwd, PATH_MAX) == NULL)
		return (error("cd", NULL), ERR_CHDIR);
	set_env(*env, "OLDPWD", old_pwd);
	if (node->argc == 1 || ft_strcmp(node->args[1], "~") == 0)
		status = handle_home_dir(env);
	else if (ft_strcmp(node->args[1], "-") == 0)
		status = handle_prev_dir(env);
	else
	{
		if (chdir(node->args[1]) == -1)
			return (error("cd", NULL), ERR_CHDIR);
		status = EXIT_SUCCESS;
	}
	if (status == EXIT_SUCCESS)
		update_pwd(*env, old_pwd, node->args[1]);
	return (status);
}

/*
	int stat(const char *path, struct stat *buf);
	- path:the path to the file or dir you want to query.
	- buf:  where the file's information will be stored.
	0: Success. The struct stat pointed to by buf is filled with the file's info.
	-1: Failure. The global variable errno is set to indicate the error
*/
int	builtin_cd(t_ast_node *node, t_env **env)
{
	char		*tmp;
	char		old_pwd[PATH_MAX];
	struct stat	info;

	if (getcwd (old_pwd, PATH_MAX) == NULL)
		return (error("cd", NULL), EXIT_FAILURE);
	if (node->argc == 1 || ft_strcmp(node->args[1], "-") == 0
		|| ft_strcmp(node->args[1], "~") == 0)
		return (cd_dir(node, env));
	else
	{
		if (access(node->args[1], F_OK) == -1)
			return (error("cd", "No such file or directory"), EXIT_FAILURE);
		if (stat(node->args[1], &info) == -1)
			return (error("cd", NULL), EXIT_FAILURE);
		if (!S_ISDIR(info.st_mode))
			return (error("cd", "Is not a dir"), EXIT_FAILURE);
		if (access(node->args[1], R_OK | X_OK) == -1)
			return (error("cd", "Permission denied"), EXIT_FAILURE);
		if (chdir(node->args[1]) == -1)
			return (error("cd", NULL), EXIT_FAILURE);
		tmp = node->args[1];
	}
	update_pwd(*env, old_pwd, tmp);
	return (set_underscore(node->argc, node->args), EXIT_SUCCESS);
}
