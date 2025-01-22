/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 15:14:26 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/22 21:25:03 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"

static int	ft_unset(t_exec *cmd)
{
	t_env	*tmp;
	int		i;

	i = 1;
	while (i < cmd->argc)
	{
		tmp = get_env(*(cmd)->env, cmd->argv[i]);
		if (tmp)
			tmp->hide = true;
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	builtin_env(t_exec *cmd)
{
	t_env	*head;

	if (cmd->argc > 1)
	{
		ft_putendl_fd("Too many args", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	head = *(cmd->env);
	while (head)
	{
		if (head->hide == false && (head->scope & (BOTH | ENVE)))
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	return (EXIT_SUCCESS);
}

/*
	If the getcwd function fails, it return 1, otherwise returns 1.
*/
static int	builtin_pwd(t_exec *cmd)
{
	char	cwd[PATH_MAX];

	if (cmd->argc != 1)
		return (ft_putendl_fd(MANY_ARGS_ERROR, STDERR_FILENO), 1);
	getcwd(cwd, PATH_MAX);
	printf("%s\n", cwd);
	return (EXIT_SUCCESS);
}
/*
	echo with -n do not output the trailing newline
	echo with no args, output a newline
	echo with multiple -n, skip those -n
	echo with invalid -n, e.g. -nn, will directly output -nn
*/
static int	builtin_echo(t_exec *cmd)
{
	int	i;
	int	no_newline;

	i = 1;
	no_newline = -1;
	if (cmd->argv[i] && ft_strncmp(cmd->argv[++i], "-n", 3) == 0)
		no_newline = 1;
	while (cmd->argv[i])
	{
		if (ft_strcmp(cmd->argv[i], "$?") == 0) //$? case included
		{
			printf("%d", get_exit_status());
			i++;
			continue;
		}
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1])
			printf(" ");
		i++;
	}
	if (!no_newline)
		printf("\n");
	return (EXIT_SUCCESS);
}

int	execute_builtin(t_exec *cmd)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (1);
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (builtin_cd(cmd));
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(cmd));
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (builtin_exit(cmd));
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (builtin_env(cmd));
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (builtin_pwd(cmd));
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (builtin_export(cmd));
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (builtin_unset(cmd));
	return (0);
}
