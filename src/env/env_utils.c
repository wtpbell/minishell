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
	// printf("Debug - searching for key: %s\n", key); // Debug
	while (envs)
	{
		// printf("Debug - checking env: key=%s, value=%s, hide=%d\n", 
			// envs->key, envs->value ? envs->value : "NULL", envs->hide); //debug
		if (ft_strcmp(envs->key, key) == 0 && envs->hide == false)
			return (envs->value);
		envs = envs->next;
	}
	return (NULL);
}

static bool	exist_key(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (true);
		env = env->next;
	}
	return (false);
}

void	add_env_var(t_env **env, char *key, char *value)
{
	t_env	*new_env;

	printf("Debug - add_env_var: key=%s, value=%s\n", key, value ? value : "NULL"); // Debug
	new_env = (t_env *)malloc(sizeof(t_env));
	if(!new_env)
		return ;
	new_env->key = key;
	if (value)
		new_env->value = ft_strdup(value);
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
