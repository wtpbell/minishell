/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 15:14:16 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/23 18:33:31 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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

int		builtin_cd(t_ast_node *node, t_env **env)
{
	
}
