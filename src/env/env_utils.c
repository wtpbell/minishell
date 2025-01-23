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

void	setup_shlvl(t_env *new)
{
	int	old_shlvl;

	if (new->value)
	{
		old_shlvl = ft_atoi(new->value);
		if (old_shlvl < 0)
			new->value = ft_atoi(0);
		else if (old_shlvl >= 999)
		{
			ft_putstr_fd("minishell: warning: shell level(1000) ", 2);
			ft_putendl_fd("too high, resetting to 1", 2);
			new->value = ft_itoa(1);
		}
		else
			new->value = ft_itoa(++old_shlvl);
		free(new->value); //it shd be free
	}
}
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
