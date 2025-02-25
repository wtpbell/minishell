/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_set.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 15:44:06 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/23 23:34:07 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "executor.h"
#include "common.h"

// Helper function to add new node to env list
void	add_env(t_env **env, t_env *new)
{
	t_env	*curr;

	if (!env || !new)
		return ;
	if (!*env)
	{
		*env = new;
		new->prev = NULL;
		return ;
	}
	curr = *env;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
	new->prev = curr;
	new->next = NULL;
}

void	set_env(t_env *envs, const char *key, const char *new_value)
{
	while (envs)
	{
		if (ft_strcmp(envs->key, key) == 0)
		{
			envs->hide = false;
			envs->value = NULL;
			if (envs->scope != SPECIAL && ft_strcmp(envs->key, "_") != 0)
				envs->scope = BOTH;
			if (new_value)
			{
				envs->value = mem_strdup(new_value);
				if (!envs->value)
					return ;
			}
			else if (envs->scope != SPECIAL && ft_strcmp(envs->key, "_") != 0)
				envs->scope = EXPORT;
			return ;
		}
		envs = envs->next;
	}
}

/*
	_ is automatically updated by the shell to store:
	- The last argument of the last command.
	- Or the full path of the executed command if there are no arguments.
*/
void	set_underscore(int argc, char **args)
{
	char	**splited;
	int		i;

	if ((argc - 1) != 0)
	{
		set_env(*get_env_list(), "_", args[argc - 1]);
		return ;
	}
	splited = mem_split(args[argc - 1], "/");
	if (!splited)
		return ;
	i = 0;
	while (splited[i])
		i++;
	if (i == 0)
		i = 1;
	if (i > 0)
		set_env(*get_env_list(), "_", splited[i - 1]);
	free_alloc(splited);
}

/*
	Set the _ environment variable to:
	-The last argument if there are arguments (argc > 1)
	-An empty string if there are no arguments
*/
void	set_last(char **args, int argc)
{
	if (!args)
		return ;
	if (argc > 1)
		set_env(*get_env_list(), "_", args[argc - 1]);
	else
		set_env(*get_env_list(), "_", "");
}
