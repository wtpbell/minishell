/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_set.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 15:44:06 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/05 13:54:45 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"
#include "executor.h"

void	add_env(t_env **env, t_env *new)
{
	t_env	*head;

	head = *env;
	if (!head)
		*env = new;
	else
	{
		while (head->next)
			head = head->next;
		head->next = new;
		new->prev = head;
	}
}

void	set_env(t_env *envs, const char *key, const char *new_value)
{
	while (envs)
	{
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
	splited = ft_split_mini(args[argc - 1], "/");
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

/*
	Set the _ environment variable to:
	-The last argument if there are arguments (argc > 1)
	-An empty string if there are no arguments
*/
void	set_last_arg_env(char	**args, int	argc)
{
	if (!args)
		return ;
	if (argc > 1)
		set_env(*get_env_list(), "_", args[argc - 1]);
	else
		set_env(*get_env_list(), "_", "");
}

/*
	Convert env variables into an arrray of strings, formatted as
	"key=value" for execve() as executing a new process with execve(),
	we need to pass environment variables as a char ** array
*/
char	**env_to_arr(t_env *envs)
{
	char	**env;
	int		i;
	t_env	*head;
	char	*tmp;
	char	*full_entry;

	if (!envs)
		return (NULL);
	head = envs;
	i = 0;
	while (head)
	{
		i += (head->hide == 0);
		head = head->next;
	}
	env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = -1;
	head = envs;
	while (head)
	{
		if (head->hide == 0)
		{
			tmp = ft_strjoin(head->key, "=");
			if (head->value)
			{
				full_entry = ft_strjoin(tmp, head->value);
				free(tmp);
				tmp = full_entry;
			}
			env[++i] = tmp;
		}
		head = head->next;
	}
	env[++i] = NULL;
	return (env);
}
