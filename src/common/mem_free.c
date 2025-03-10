/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_free.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/04 21:39:14 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/10 18:29:37 by bewong        ########   odam.nl         */
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

void	free_exit_memory(t_ast_node *node, t_env **env, t_token *tokens)
{
	if (node)
		free_ast(node);
	if (tokens)
		free_tokens(tokens);
	if (env)
		free_env(env);
	rl_clear_history();
}

void	exit_shell(int status, t_ast_node *node, t_env **env, t_token *tokens)
{
	free_exit_memory(node, env, tokens);
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
