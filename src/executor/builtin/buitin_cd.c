/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   buitin_cd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 15:14:16 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/21 21:23:51 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"


void	update_oldpwd(t_exec *cmd)
{
	
}

int	builtin_cd(t_exec *cmd)
{
	if (cmd->argv[1] && cmd->argv[2])
	{
		*cmd->exitcode = error_msg("cd: too many arguments", 0);
		return (1);
	}
	if (cmd->argv[1] == NULL || cmd->argv[1][0] == '~')
	{
		if (!cmd->go_home(cmd))
		{
			*cmd->exitcode = error_msg("cd: HOME not set", 0);
			return (1);
		}
		return (0);
	}
	if (cmd->argv[1][0] == '\0')
	{
		*cmd->exitcode = error_msg("cd: invalid directory", 0);
		return (1);
	}
	if (chdir(cmd->argv[1]) == 0)
	{
		update_oldpwd(cmd);
		update_pwd(cmd);
		*cmd->exitcode = 0;
		return (0);
	}
	 *cmd->exitcode = error_msg_format("cd: %s: No such file or directory", cmd->argv[1]);
	return (1);
}

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
