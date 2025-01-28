/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_set.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 15:44:06 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/28 18:17:03 by bewong        ########   odam.nl         */
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
		set_env(*get_env_list(), '_', args[argc - 1]);
		return	;
	}
	splited = ft_split(args[argc - 1], "/");
	if (!splited)
		return ;
	i = 0;
	while (splited[i])
		i++;
	if (i == 0)
		i = 1;
	if (i > 0)
		set_env(*get_env_list(), '_', splited[i - 1]);
	free(splited); //free splited;
}
