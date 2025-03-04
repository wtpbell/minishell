/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_free.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/04 21:39:14 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/04 21:42:31 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "minishell.h"
#include "executor.h"
#include <stdio.h>


void	free_env(t_env **env)
{
	t_env	*tmp;

	if (!env || !*env)
		return ;
	while (*env)
	{
		tmp = (*env)->next;
		if (tmp)
			tmp->prev = NULL;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = tmp;
	}
	*env = NULL;
}

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_exit_memory(t_ast_node *node, t_env **env, t_token *tokens)
{
	if (node)
	{
		free_ast(node);
	}
	if (tokens)
		free_tokens(tokens);
	if (env)
		free_env(env);
	rl_clear_history();
}
