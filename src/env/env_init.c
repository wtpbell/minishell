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

static t_env	*env_int(char **key_value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->key = key_value[0];
	new->value = key_value[1];
	new->scope = BOTH;
	new->hide = false;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
/*
	OLDPWD: Initialized with NULL value and scope set to EXPORT.
	- cd /new/path, then cd -, it uses OLDPWD to return to the previous directory.
	SHLVL: tracks how many nested shells are currently active and is incremented or reset if missing.
	_: Represents the last executed command; its scope is set to ENVE.
	?: Special variable representing the exit status of the last command.
*/
t_env *create_env(char *env)
{
	t_env *new;
	char **key_value;

	key_value = ft_split_mini(env, "=");
	if (!key_value)
		return (NULL); // need to free memory?
	new = env_int(key_value);
	if (ft_strcmp(new->key, "OLDPWD") == 0)
	{
		new->value = NULL; //just start, no previous directory
		new->scope = EXPORT; //exported to child processes when creating new shell
	}
	else if (ft_strcmp(new->key, "SHLVL") == 0)
		setup_shlvl(new);
	else if (ft_strcmp(new->key, "_") == 0)
		new->scope = ENVE;
	else if (ft_strcmp(new->key, "?") == 0)
		new->scope = SPECIAL;
	return (new);
}

static void	add_empty_env(t_env **env)
{
	t_env	*new[5];
	char	pwd[PATH_MAX];
	char	*pwd2;
	int		i;

	i = 0;
	getcwd(pwd, PATH_MAX);
	new[0] = create_env("OLDPWD");
	pwd2 = ft_strjoin("PWD=", pwd);
	new[1] = create_env(pwd2);
	new[2] = create_env("SHLVL=0");
	new[3] = create_env("PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	new[3]->scope = SPECIAL;
	new[4] = create_env("_=/usr/bin/env");
	new[4]->scope = ENVE;
	while (i < 5)
		add_env(env, new[i++]);
}

t_env	*build_env(char **env)
{
	t_env	*envs;
	t_env	*news;
	int		i;

	envs = NULL;
	i = -1;
	add_env(&envs, create_env("?=0"));
	if (!env[0])
		add_empty_env(&envs);
	while(env[++i])
	{
		news = create_env(env[i]);
		add_env(&envs, news);
	}
	return (envs);
}

void	setup_shlvl(t_env *new)
{
	int	old_shlvl;

	if (new->value)
	{
		old_shlvl = ft_atoi(new->value);
		if (old_shlvl < 0)
			new->value = ft_itoa(0);
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

t_env	**get_env_list(void)
{
	static t_env	*env = NULL;

	return (&env);
}
