/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_set.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 15:44:06 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/30 17:55:26 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

void	add_env(t_env **env, t_env *new)
{
	t_env	*head;

	if (!*env)
	{
		*env = new;
		new->prev = NULL;
		new->next = NULL;
		return;
	}
	head = *env;
	while (head->next)
		head = head->next;
	head->next = new;
	new->prev = head;
	new->next = NULL;
}

void	set_env(t_env *envs, const char *key, const char *new_value)
{
	while (envs)
	{
		if (!envs->key)  // ✅ Prevent NULL pointer dereference
		{
			printf("Error: envs->key is NULL\n");
			return;
		}
		if (ft_strcmp(envs->key, key) == 0)
		{
			envs->hide = false;
			envs->value = NULL;
			if (envs->scope != SPECIAL && ft_strcmp(envs->key, "_") != 0)
				envs->scope = BOTH;
			if (new_value)
				envs->value = ft_strdup(new_value);
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
		return	;
	}
	splited = ft_split(args[argc - 1], '/');
	if (!splited)
		return ;
	i = 0;
	while (splited[i])
		i++;
	if (i == 0)
		i = 1;
	if (i > 0)
		set_env(*get_env_list(), "_", splited[i - 1]);
	free(splited); //free splited;
}
