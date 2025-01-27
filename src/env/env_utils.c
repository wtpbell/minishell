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

#include "executor.h"
#include "env.h"
#include "minishell.h"


t_env	*get_env(t_env *envs, const char *key)
{
	while (envs)
	{
		if (ft_strcmp(envs->key, key) == 0 && !envs->hide)
			return (envs);
		envs = envs->next;
	}
	return (NULL);
}

char	*get_env_value(t_env *envs, const char *key)
{
	while (envs)
	{
		if (ft_strcmp(envs->key, key) == 0 && !envs->hide)
			return (envs->key);
		envs = envs->next;
	}
	return (NULL);
}

char	**rebuild_env_to_char(t_env *envs)
{
	char	**env;
	int		i;

	i = 0;
	for (t_env *tmp = envs; tmp; tmp = tmp->next)
		if (!tmp->hide)
			i++;

	env = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envs)
	{
		if (!envs->hide)
		{
			env[i] = malloc(strlen(envs->key) + strlen(envs->value) + 2);
			sprintf(env[i], "%s=%s", envs->key, envs->value);
			i++;
		}
		envs = envs->next;
	}
	env[i] = NULL;
	return (env);
}

