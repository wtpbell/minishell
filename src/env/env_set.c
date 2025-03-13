/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_set.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 15:44:06 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/13 10:17:41 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "executor.h"
#include "common.h"

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

static void	set_scope(t_env *envs, const char *new_value)
{
	if (envs->scope != SPECIAL && ft_strcmp(envs->key, "_") != 0 && \
		ft_strcmp(envs->key, "?") != 0)
	{
		if (new_value)
			envs->scope = BOTH;
		else
			envs->scope = EXPORT;
	}
}

void	set_env(t_env *envs, const char *key, const char *new_value)
{
	while (envs)
	{
		if (ft_strcmp(envs->key, key) == 0)
		{
			envs->hide = false;
			if (envs->value)
			{
				free(envs->value);
				envs->value = NULL;
			}
			set_scope(envs, new_value);
			if (new_value)
			{
				envs->value = ft_strdup(new_value);
				if (!envs->value)
					return ;
			}
			return ;
		}
		envs = envs->next;
	}
}

void	set_underscore(int argc, char **args)
{
	char	**splited;
	int		i;

	if (argc < 1 || !args || !args[0])
		return ;
	if ((argc - 1) != 0)
	{
		set_env(*get_env_list(), "_", args[argc - 1]);
		return ;
	}
	splited = mem_split(args[argc - 1], "/");
	if (!splited)
		return ;
	i = 0;
	while (splited[i + 1])
		i++;
	set_env(*get_env_list(), "_", splited[i]);
	free_tab(splited);
}

void	set_last(char **args, int argc)
{
	if (!args)
		return ;
	if (argc > 1)
		set_env(*get_env_list(), "_", args[argc - 1]);
	else
		set_env(*get_env_list(), "_", "");
}
