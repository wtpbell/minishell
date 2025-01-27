/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_set.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 15:44:06 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/27 18:44:27 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "env.h"
#include "minishell.h"

void	add_env(t_env **env, t_env *new)
{
	t_env	*head;

	if (!env || !new)
		return ;
	if (!*env)
		*env = new;
	head = *env;
	while (head->next)
		head = head->next;
	head->next = new;
	new->prev = head;
}

int	set_env(t_env *envs, const char *key, const char *new_value)
{
	if (!key || !*key)
		return (0);
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
			if (envs->scope != SPECIAL && ft_strcmp(envs->key, "_") != 0)
				envs->scope = BOTH;
			if (new_value)
				envs->value = ft_strdup(new_value);
			else if (envs->scope != SPECIAL && ft_strcmp(envs->key, "_") != 0)
				envs->scope = EXPORT;
			return (1);
		}
		envs = envs->next;
	}
	return (0);
}

void	set_underscore(int argc, char **argv)
{
	
}
