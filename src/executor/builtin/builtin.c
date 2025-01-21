/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 15:14:26 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/21 23:09:10 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	builtin_env(t_exec *cmd)
{
	char	**env;
	int		i;

	if (!cmd->env_ptr || !*cmd->env_ptr)
	{
		*cmd->exitcode = 1;
		return (error_msg("env: environment not set"));
	}
	env = *cmd->env_ptr;
	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	*cmd->exitcode = 0;
	return (1);
}

/*
	If the getcwd function fails, it return 1, otherwise returns 1.
*/
int	builtin_pwd(t_exec *cmd)
{
	char	*pwd;
	char	buffer[PATH_MAX];

	pwd = getcwd(buff, PATH_MAX);
	if (pwd != NULL)
		printf("%s\n", pwd);
	*group->exitcode = 0;
	return (1);
}
/*
	echo with -n do not output the trailing newline
	echo with no args, output a newline
	echo with multiple -n, skip those -n
	echo with invalid -n, e.g. -nn, will directly output -nn
*/
int	builtin_echo(t_exec *cmd)
{
	int	i;
	int	no_newline;

	i = 1;
	if (cmd->argv[i] && !ft_strncmp(cmd->argv[i], "-n", 3))
	{
		no_newline = 1;
		i++;
	}
	while (cmd->argv[i])
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[++i])
			printf(" ");
	}
	if (!no_newline)
		printf("\n");
	*cmd->exitcode = 0;
	return (1);
}

int	builtin(t_exec *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	if (ft_strncmp(cmd->argv[0], "cd", 3) == 0)
		return (builtin_cd(cmd));
	if (ft_strncmp(cmd->argv[0], "echo", 5) == 0)
		return (builtin_echo(cmd));
	if (ft_strncmp(cmd->argv[0], "exit", 5) == 0)
		return (builtin_exit(cmd));
	if (ft_strncmp(cmd->argv[0], "env", 4) == 0)
		return (builtin_env(cmd));
	if (ft_strncmp(cmd->argv[0], "pwd", 4) == 0)
		return (builtin_pwd(cmd));
	if (ft_strncmp(cmd->argv[0], "export", 7) == 0)
		return (builtin_export(cmd));
	if (ft_strncmp(cmd->argv[0], "unset", 6) == 0)
		return (builtin_unset(cmd));
	return (0);
}
