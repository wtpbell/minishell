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

static bool	exist_key(t_env *env, char *key)
{
	return (get_env(env, key) != NULL);
}

void	add_env_var(t_env **env, char *key, char *value)
{
	t_env	*new_env;

	new_env = (t_env *)mem_alloc(sizeof(t_env));
	if (!new_env)
		return ;
	new_env->key = key;
	if (value)
	{
		new_env->value = mem_strdup(value);
		if (!new_env->value)
			return ;
	}
	else
		new_env->value = NULL;
	new_env->hide = false;
	new_env->scope = BOTH;
	if (value == NULL)
		new_env->scope = EXPORT;
	new_env->next = NULL;
	new_env->prev = NULL;
	if (exist_key(*(env), key))
		set_env(*(env), key, value);
	else
		add_env(env, new_env);
}

void	setup_shlvl(t_env *new)
{
	int	old_shlvl;

	if (new->value)
	{
		old_shlvl = ft_atoi(new->value);
		if (old_shlvl < 0)
			new->value = mem_itoa(0);
		else if (old_shlvl >= 999)
		{
			ft_putstr_fd("minishell: warning: shell level(1000) ", 2);
			ft_putendl_fd("too high, resetting to 1", 2);
			new->value = mem_itoa(1);
		}
		else
			new->value = mem_itoa(++old_shlvl);
		if (!new->value)
			return ;
	}
}
