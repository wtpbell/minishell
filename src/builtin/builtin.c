/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 15:14:26 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/13 22:50:30 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	builtin_unset(t_ast_node *node, t_env **env, t_token *tokens)
{
	t_env	*tmp;
	int		i;

	(void)tokens;
	i = 1;
	while (i < node->argc)
	{
		tmp = get_env(*env, node->args[i]);
		if (tmp)
			tmp->hide = true;
		i++;
	}
	return (set_underscore(node->argc, node->args), EXIT_SUCCESS);
}

static int	builtin_env(t_ast_node *node, t_env **env, t_token *tokens)
{
	t_env	*head;

	(void)tokens;
	set_underscore(node->argc, node->args);
	if (node->argc > 1)
	{
		ft_putendl_fd(MANY_ARGS_ERROR, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	head = *env;
	while (head)
	{
		if (head->hide == false && (head->scope & (BOTH | ENV)))
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
	return (EXIT_SUCCESS);
}

static int	builtin_pwd(t_ast_node *node, t_env **env, t_token *tokens)
{
	char	cwd[PATH_MAX];

	(void)env;
	(void)tokens;
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ft_putendl_fd(NON_EXIST_DIR, STDERR_FILENO), 1);
	printf("%s\n", cwd);
	return (set_underscore(node->argc, node->args), EXIT_SUCCESS);
}

int	(*is_builtin(char *args))(t_ast_node *node, t_env **env, t_token *token)
{
	if (!args || !args[0])
		return (NULL);
	if (ft_strcmp(args, "pwd") == 0)
		return (builtin_pwd);
	else if (ft_strcmp(args, "env") == 0)
		return (builtin_env);
	else if (ft_strcmp(args, "unset") == 0)
		return (builtin_unset);
	else if (ft_strcmp(args, "echo") == 0)
		return (builtin_echo);
	else if (ft_strcmp(args, "cd") == 0)
		return (builtin_cd);
	else if (ft_strcmp(args, "exit") == 0)
		return (builtin_exit);
	else if (ft_strcmp(args, "export") == 0)
		return (builtin_export);
	return (NULL);
}
