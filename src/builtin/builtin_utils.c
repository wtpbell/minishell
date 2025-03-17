/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 17:22:19 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/16 14:27:49 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "common.h"

static void	ft_swap(t_env *a, t_env *b)
{
	char	*temp_key;
	char	*temp_value;
	t_scope	temp_scope;
	bool	temp_hide;

	temp_key = a->key;
	temp_value = a->value;
	temp_scope = a->scope;
	temp_hide = a->hide;
	a->key = b->key;
	a->value = b->value;
	a->scope = b->scope;
	a->hide = b->hide;
	b->key = temp_key;
	b->value = temp_value;
	b->scope = temp_scope;
	b->hide = temp_hide;
}

void	sort_env(t_env **envs)
{
	t_env	*env;
	bool	did_swap;

	if (!envs || !*envs || !(*envs)->next)
		return ;
	did_swap = true;
	while (did_swap)
	{
		env = *envs;
		did_swap = false;
		while (env->next)
		{
			if (ft_strcmp(env->key, env->next->key) > 0)
			{
				ft_swap(env, env->next);
				did_swap = true;
			}
			env = env->next;
		}
	}
}

void	env_args_handler(t_env **env, char **split, char *args)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	env_args_dup(split, &key, &value);
	if (args[ft_strlen(args) - 1] == '=')
	{
		if (value)
		{
			free(value);
			value = NULL;
		}
		add_env_var(env, key, "");
	}
	else if (key && !value)
		add_env_var(env, key, NULL);
	else
		add_env_var(env, key, value);
	free(key);
	if (value)
		free(value);
}

void	env_args_dup(char **split, char **key, char **value)
{
	*key = ft_strdup(split[0]);
	if (!*key)
	{
		free_tab(split);
		return ;
	}
	if (split[1])
		*value = ft_strdup(split[1]);
	else
		*value = NULL;
	free_tab(split);
}
