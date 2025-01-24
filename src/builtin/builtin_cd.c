/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 15:14:16 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/24 19:47:52 by bewong        ########   odam.nl         */
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

int	cd_dir(t_ast_node *node)
{
	char	old_pwd[PATH_MAX];

	if(getcwd(old_pwd, PATH_MAX) == NULL)
		return (errno); //need to chec what error msg;
	if (node->args_count == 1 || ft_strcmp(node->args[1], '~') == 0)
	
}

int	builtin_cd(t_ast_node *node, t_env **env)
{
	char		*tmp;
	char		old_pwd[PATH_MAX];
	struct stat	info;

	if (getcwd(old_pwd, PATH_MAX) == NULL)
		return (errno); //need to check what error msg;
	if (node->args_count == 1 || ft_strcmp(node->args[1], '-') == 0
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
		if (!stat(node->args[1],&info))
			return (error("cd", NULL), EXIT_FAILURE);
		if (chdir(node->args[1]) == -1)
			return (error("cd", NULL), EXIT_FAILURE);
		tmp = node->args[1];
	}	
	return (update_env(env, "OLDPWD", old_pwd) || update_env(env, "PWD", tmp));
}
