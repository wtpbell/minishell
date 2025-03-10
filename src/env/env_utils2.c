/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/22 11:08:40 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/22 11:08:40 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "executor.h"
#include "common.h"

t_env	*get_env(t_env *envs, const char *key)
{
	while (envs)
	{
		if (ft_strcmp(envs->key, key) == 0 && envs->hide == false)
			return (envs);
		envs = envs->next;
	}
	return (NULL);
}

char	*get_env_value(t_env *envs, const char *key)
{
	while (envs)
	{
		if (ft_strcmp(envs->key, key) == 0 && envs->hide == false)
			return (envs->value);
		envs = envs->next;
	}
	return (NULL);
}

static void	added_env_init(t_env *new_env, char *key, char **value)
{
	new_env->key = ft_strdup(key);
	if (!new_env->key)
	{
		free(new_env);
		return ;
	}
	if (*value)
	{
		new_env->value = ft_strdup(*value);
		if (!new_env->value)
		{
			free(new_env->key);
			free(new_env);
			return ;
		}
	}
	else
		new_env->value = NULL;
	new_env->hide = false;
	new_env->scope = BOTH;
	if (*value == NULL)
		new_env->scope = EXPORT;
	new_env->next = NULL;
	new_env->prev = NULL;
}

void	add_env_var(t_env **env, char *key, char *value)
{
	t_env	*new_env;

	if (get_env(*env, key))
	{
		set_env(*env, key, value);
		return ;
	}
	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		return ;
	added_env_init(new_env, key, &value);
	add_env(env, new_env);
}
