/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 15:14:16 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/27 18:41:08 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
/*
	Command				Expected Behavior
	cd dir1				Changes to dir1.
	cd nonexistent_dir	Prints "cd: nonexistent_dir: No such file or directory".
	cd					Goes to the home directory.
	cd ~				Goes to the home directory.
	cd ""				Prints "cd: invalid directory".
	cd dir1 dir2		Prints "cd: too many arguments".
	cd /path/to/file	Fails if /path/to/file is not a directory.
	cd ..				Goes to the parent directory.
*/

static void	update_pwd(t_env *envs, char *old_pwd, char *pwd)
{
	if (set_env(envs, "OLDPWD", old_pwd) == 0)
		error("cd", "Failed to update OLDPWD");
	if (set_env(envs, "PWD", pwd) == 0)
		error("cd", "Failed to update PWD");
}

static int	cd_dir(t_ast_node *node)
{
	char	old_pwd[PATH_MAX];
	char	*tmp;

	if(getcwd(old_pwd, PATH_MAX) == NULL)
		return (error("cd", NULL), EXIT_FAILURE);
	tmp = NULL;
	if (node->argc == 1 || ft_strcmp(node->args[1], '~') == 0)
	{
		tmp = get_env_value(*(node->env), "HOME");
		if (!tmp)
			return (error("cd", "HOME not set"), EXIT_FAILURE);
		if (chdir(tmp) == -1)
			return (EXIT_FAILURE);
	}
	else if (node->argc == 1 || ft_strcmp(node->args[1], '-') == 0)
	{
		tmp = get_env_value(*(node->env), "OLDPWD");
		if (!tmp)
			return (error("cd", "OLDPWD not set"), EXIT_FAILURE);
		tmp = ft_strdup(tmp);
		if (chdir(tmp) == -1)
			return (error("cd", NULL), EXIT_FAILURE);
		ft_putendl_fd(tmp, STDOUT_FILENO);
	}
	update_pwd(*(node->env), old_pwd, tmp);
	return (EXIT_SUCCESS);
}

/* 
	int stat(const char *path, struct stat *buf);
	- path: A string representing the path to the file or directory you want to query.
	- buf: A pointer to a struct stat, where the file's information will be stored.
	0: Success. The struct stat pointed to by buf is filled with the file's information.
	-1: Failure. The global variable errno is set to indicate the error 
*/
int	builtin_cd(t_ast_node *node, t_env **env)
{
	char		*tmp;
	char		old_pwd[PATH_MAX];
	struct stat	info;

	if (getcwd(old_pwd, PATH_MAX) == NULL)
		return (error("cd", NULL), EXIT_FAILURE);
	if (node->argc == 1 || ft_strcmp(node->args[1], '-') == 0
		|| ft_strcmp(node->args[1], '~') == 0)
		return (cd_dir(node));
	else
	{
		if (access(node->args[1], F_OK) == -1)
			return (error("cd", "no such file or directory"), EXIT_FAILURE);
		if (!S_ISDIR(info.st_mode))
			return (error("cd", "not a directory"), EXIT_FAILURE);
		if (access(node->args[1], R_OK || X_OK) == -1)
			return (error("cd", "Permission denied"), EXIT_FAILURE);
		if (stat(node->args[1],&info) == -1)
			return (error("cd", NULL), EXIT_FAILURE);
		if (chdir(node->args[1]) == -1)
			return (error("cd", NULL), EXIT_FAILURE);
		tmp = node->args[1];
	}	
	update_pwd(*(node->env), old_pwd, tmp);
	return ();
}
