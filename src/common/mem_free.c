/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_free.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/04 21:39:14 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/05 00:05:24 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "minishell.h"
#include "executor.h"
#include <stdio.h>


void	free_env(t_env **env)
{
	t_env	**env_list;
	t_env	*current;
	t_env	*next;

	(void) env;
	env_list = get_env_list();
	if (env_list && *env_list)
	{
		current = *env_list;
		while (current)
		{
			next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			current = next;
		}
		*env_list = NULL;
	}
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
		free_ast(node);
	if (tokens)
		free_tokens(tokens);
	if (env)
		free_env(env);
	rl_clear_history();
}

// void	remove_env_var(t_env **env, const char *key)
// {
// 	t_env *curr;

// 	if (!env || !*env || !key)
// 		return ;

// 	curr = *env;
// 	while (curr)
// 	{
// 		if (ft_strcmp(curr->key, key) == 0)
// 		{
// 			remove_env_node(env, curr);
// 			return ;
// 		}
// 		curr = curr->next;
// 	}
// }

// void	remove_env_node(t_env **head, t_env *node)
// {
// 	if (!head || !*head || !node)
// 		return ;
// 	if (node->prev)
// 		node->prev->next = node->next;
// 	else
// 		*head = node->next;
// 	if (node->next)
// 		node->next->prev = node->prev;
// 	free(node->key);
// 	free(node->value);
// 	free(node);
// }

// void	free_child_info(t_child_info *child)
// {
// 	if (!child)
// 		return ;

// 	if (child->input > 0)
// 		close(child->input);
// 	if (child->output > 0)
// 		close(child->output);
// 	if (child->new_input > 0)
// 		close(child->new_input);
// 	if (child->tokens)
// 	{
// 		free_tokens(child->tokens);
// 		child->tokens = NULL;
// 	}
// }
