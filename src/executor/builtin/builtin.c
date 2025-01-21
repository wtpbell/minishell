#include "builtin.h"

/*
	No Arguments: Exits with status 0 (default).
	Single Numeric Argument: Exits with the given status.
	Single Non-Numeric Argument: Displays an error and exits with status 2.
	Multiple Arguments: Displays an error and does not exit.
*/
int	builtin_exit(t_cmd *cmd)
{
	int	exit_code;

	printf("exit\n");
	if (cmd->argv[1] && cmd->argv[2])
		return (*cmd->exitcode = error_msg("exit: too many arguments"), 1);
	exit_code = 0;
	if (cmd->argv[1] &&ft_isnumber(cmd->argv[1]))
		exit_code = ft_atoi(cmd->argv[1]);
	else if (cmd->argv[1])
		exit_code = 2 * error_msg("exit: numeric argument required");
	//need to free memory//
	return (1);
}

int	builtin_env(t_cmd *cmd)
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
int	builtin_pwd(t_cmd *cmd)
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
int	builtin_echo(t_cmd *cmd)
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

int	builtin(t_cmd *cmd)
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
