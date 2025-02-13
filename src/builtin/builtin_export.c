/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 15:14:34 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/13 12:31:08 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "env.h"
#include "builtin.h"
#include "common.h"

static void	print_envs(t_env *env)
{
	while (env)
	{
		if (env->hide == false && (env->scope & (BOTH | EXPORT)))
		{
			printf("%s", DECLARE);
			printf("%s", env->key);
			if (env->value != NULL)
				printf("=\"%s\"\n", env->value);
			else
				printf("\n");
		}
		env = env->next;
	}
}
/*
	check if a valid variable name starts with a letter (A-Z or a-z) or
	an underscore (_) but cannot start with a number or special character.
*/
static bool	is_valid_key(char *key)
{
	int	i;

	i = 0;
	if (!key)
		return (false);
	if (!(ft_isalpha(key[i]) || key[i] == '_'))
		return (false);
	while (ft_isalpha(key[i]) || key[i] == '_')
		i++;
	while (ft_isalpha(key[i]) || key[i] == '_' || ft_isdigit(key[i]))
		i++;
	if (key[i] == '\0')
		return (true);
	return (false);
}

/*
	This function appends a new value to an existing environment variable 
	if the key ends with +. If the key does not end with +, nothing special happens.
*/
static void	append_env_value(t_env *env, char **key, char **value)
{
	char	*key_;
	char	*value_;
	char	*tmp;
	
	key_ = *key;
	value_ = *value;
	if (!key_ || !value_)
		return ;
	if (key_[ft_strlen(key_) - 1] == '+')
	{
		tmp = key_;
		*key = mem_substr(key_, 0, (ft_strlen(key_) - 1));
		free_alloc(tmp);
		if (value_ == NULL)
			return ;
		tmp = value_;
		*value = mem_strjoin(get_env_value(env, (*key)), value_);
		if (tmp != NULL)
			free_alloc(tmp);
		return ;
	}
}

static void	modify_env(t_env **env, char *args)
{
	char	**split;

	split = mem_split(args, "=");
	if (!split)
		return ;
	// printf("Debug - export args: %s\n", args); //debug
	// if (split[0])
	// 	printf("Debug - key: %s. value: %s\n", split[0], split[1]); //debug
	if (split[0])
		append_env_value((*env), &split[0], &split[1]);
	if (!is_valid_key(split[0]) || args[0] == '=')
	{
		ft_putstr_fd(args, STDERR_FILENO);
		ft_putendl_fd(" : not a valid identifier", STDERR_FILENO);
		return ;
	}
	if (args[ft_strlen(args) - 1] == '=') 
		add_env_var(env, split[0], "");
	else if (split[0] && !split[1])
		add_env_var(env, split[0], NULL);
	else
		add_env_var(env, split[0], split[1]);
}

int	builtin_export(t_ast_node *node)
{
	int	i;

	i = 0;
	sort_env(node->env);
	if (node->argc == 1)
	{
		print_envs(*(node->env));
		return (set_underscore(node->argc, node->args), EXIT_SUCCESS);
	}
	else
	{
		while(++i < node->argc)
			modify_env(node->env, node->args[i]);
		return (set_underscore(node->argc, node->args), EXIT_SUCCESS);
	}
}
