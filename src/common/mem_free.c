/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_free.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/04 21:39:14 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/11 14:24:47 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "minishell.h"
#include "executor.h"
#include <stdio.h>

void	free_env(t_env **env)
{
	t_env	*current;
	t_env	*next;

	if (!env || !*env)
		return ;
	current = *env;
	while (current)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*env = NULL;
}

void	free_tab(char **tab)
{
	size_t	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

// extern t_ast_node *root;

void	free_exit_memory(t_ast_node *node, t_env **env, t_token *tokens)
{
	t_ast_node *root_to_free;

	(void)node;
	(void)tokens;
	ft_putendl_fd("EXITING!!!!!!!!!!!!!!!!!!!!!!!!!!!!", 2);
	root_to_free = get_root_node(NULL);
	if (root_to_free)
	{
		// dprintf(2, "%p %p\n", root_to_free, *env);
		printf("freeing root\n");
		free_ast(root_to_free);
		get_root_node(NULL);
	}
	// if (node && node != root_to_free)
	// {
	// 	printf("freeing node\n");
	// 	free_ast(node);
	// 	node = NULL;
	// }
	// if (tokens)
	// {
	// 	printf("freeing tokens\n");
	// 	free_tokens(tokens);
	// 	tokens = NULL;
	// }
	if (env && *env)
	{
		printf("freeing env\n");
		free_env(env);
		env = NULL;
	}
	rl_clear_history();
}

void	exit_shell(int status, t_ast_node *node, t_env **env, t_token *tokens)
{
	(void)node;
	(void)tokens;
	free_exit_memory(NULL, env, NULL);
	exit(status);
}

void	child_cleanup(t_ast_node *node, char **env_arr)
{
	int	i;

	i = 0;
	if (node->args)
	{
		while (node->args[i])
			free(node->args[i++]);
		free(node->args);
	}
	if (node->arg_quote_types)
		free(node->arg_quote_types);
	if (node->redirections)
		free_redirections(node->redirections);
	free(node);
	if (env_arr)
		free_tab(env_arr);
}
