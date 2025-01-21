/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 15:14:31 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/21 22:47:52 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	remove_variable(t_exec *cmd, char *name)
{
	int	i;
	int j;
	int	tablen; //current env variable array length
	int	namelen; //variable name length
	char **new_env;

	if (!cmd || !name || !cmd->env_ptr || !(*cmd->env_ptr))
			return;
	namelen = ft_strlen(name);
	tablen = tab_len(*cmd->env_ptr);
	new_env = malloc(sizeof(char *) * tablen);
	// protect env malloc
	i = -1;
	j = 0;
	while ((*cmd->env_ptr)[++i])
	{ //PATH && PATH_EXTRA below condition prevent remove wrong one
		if (!ft_strncmp((*cmd->env_ptr)[i], name, namelen) && (*cmd->env_ptr)[i][namelen] == '=')
			continue;
		new_env[j] = ft_strdup((*cmd->env_ptr)[i]);
		//handle memory
		j++;
	}
	new_env[j] = NULL;
	free_tab(*cmd->env_ptr);
	*cmd->env_ptr = new_env
}

int	builtin_unset(t_exec *cmd)
{
	int		i;

	i = 0;
	while (cmd->argv[++i])
	{
		if (get_env(*cmd->env_ptr, cmd->argv[i]) == NULL)
		{
			*cmd->exitcode = 0;
			return (1);
		}
		remove_variable(cmd, cmd->argv[i]);
	}
	*cmd->exitcode = 0;
	return (1);
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	char *env[] = {
		ft_strdup("PATH=/usr/bin"),
		ft_strdup("HOME=/home/user"),
		ft_strdup("SHELL=/bin/bash"),
		NULL
	};

	t_exec cmd;
	cmd.env_ptr = &env;
	printf("Before removing HOME:\n");
	for (int i = 0; env[i]; i++)
		printf("%s\n", env[i]);

	remove_token(&cmd, "HOME");

	printf("\nAfter removing HOME:\n");
	for (int i = 0; env[i]; i++)
		printf("%s\n", env[i]);
	free_tab(env);
	return 0;
}
