/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 15:14:26 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/23 18:49:25 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	ft_unset(t_ast_node *node, t_env **env)
{
	t_env	*tmp;
	int		i;

	if (!node || !env || !*env)
		return (EXIT_FAILURE);
	i = 1;
	while (i < node->args_count)
	{
		tmp = get_env(*env, node->args[i]);
		if (tmp)
			tmp->hide = true;
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	builtin_env(t_ast_node *node, t_env **env)
{
	t_env	*head;

	if (!node || !env || !*env)
		return (EXIT_FAILURE);
	if (node->args_count > 1)
	{
		ft_putendl_fd("Too many args", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	head = *env;
	while (head)
	{
		if (head->hide == false && (head->scope & (BOTH | ENVE)))
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	return (EXIT_SUCCESS);
}

/*
	If the getcwd function fails, it return 1, otherwise returns 1.
*/
static int	builtin_pwd(t_ast_node *node, t_env **env)
{
	char	cwd[PATH_MAX];

	if (node->args_count != 1)
		return (ft_putendl_fd(MANY_ARGS_ERROR, STDERR_FILENO), 1);
	getcwd(cwd, PATH_MAX);
	printf("%s\n", cwd);
	return (EXIT_SUCCESS);
}


int	execute_builtin(t_ast_node *node, t_env **env)
{
	char **args;

	args = node->args;
	if (!args || !args[0])
		return (g_exit_status = EXIT_FAILURE);
	if (strcmp(args[0], "cd") == 0)
		return (g_exit_status = builtin_cd(node, env));
	if (strcmp(args[0], "export") == 0)
		return (g_exit_status = builtin_export(node, env));
	if (strcmp(args[0], "unset") == 0)
		return (g_exit_status = builtin_unset(node, env));
	if (strcmp(args[0], "env") == 0)
		return (g_exit_status = builtin_env(node, env));
	if (strcmp(args[0], "echo") == 0)
		return (g_exit_status = builtin_echo(node));
	if (strcmp(args[0], "exit") == 0)
		builtin_exit(node);
	return (g_exit_status = EXIT_FAILURE);
}
