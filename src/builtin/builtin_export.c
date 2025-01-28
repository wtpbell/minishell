/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 15:14:34 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/28 18:17:40 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "env.h"
#include "minishell.h"

void	print_envs(t_env *env)
{
	int	i;

	i = 0;
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
void	modify_env(t_env **env, char *args)
{
	char	**split;

	split = ft_split(args, "=");
	if (!split)
		return (NULL);
	
	
}

int		builtin_export(t_ast_node *node)
{
	int	i;

	i = 0;
	sort_envs(node->env);
	if (node->argc == 1)
	{
		print_envs(*(node->env));
		return (set_underscore(node->argc, node->args), EXIT_SUCCESS);
	}
	else
	{
		while(++i < node->argc)
			modify_env(node->env, node->args);
		return (set_underscore(node->argc, node->args), EXIT_SUCCESS);
	}
}
