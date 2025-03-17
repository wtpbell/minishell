/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 15:14:34 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/16 17:39:22 by bewong        ########   odam.nl         */
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
		*key = ft_substr(key_, 0, (ft_strlen(key_) - 1));
		free(tmp);
		if (value_ == NULL)
		{
			*value = ft_strdup("");
			return ;
		}
		tmp = value_;
		*value = ft_strjoin(get_env_value(env, (*key)), value_);
		if (tmp != NULL)
			free(tmp);
		return ;
	}
}

static void	modify_env(t_env **env, char *args)
{
	char	**split;

	split = mem_split(args, "=");
	if (!split)
		return ;
	if (split[0])
		append_env_value((*env), &split[0], &split[1]);
	if (args[0] == '-' && args[1] != '\0')
	{
		ft_putstr_fd(args, STDERR_FILENO);
		ft_putendl_fd(" : invalid option", STDERR_FILENO);
		set_exit_status(2);
		free_tab(split);
		return ;
	}
	if (!is_valid_key(split[0]) || args[0] == '=')
	{
		ft_putstr_fd(args, STDERR_FILENO);
		ft_putendl_fd(" : not a valid identifier", STDERR_FILENO);
		set_exit_status(1);
		free_tab(split);
		return ;
	}
	env_args_handler(env, split, args);
}

int	builtin_export(t_ast_node *node, t_env **env, t_token *tokens)
{
	int	i;

	(void)tokens;
	i = 0;
	sort_env(env);
	if (node->argc == 1)
	{
		print_envs(*env);
		return (set_underscore(node->argc, node->args), EXIT_SUCCESS);
	}
	else
	{
		while (++i < node->argc)
			modify_env(env, node->args[i]);
		return (set_underscore(node->argc, node->args), get_exit_status());
	}
}
