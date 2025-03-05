/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_free.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/04 21:39:14 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/05 15:16:14 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "minishell.h"
#include "executor.h"
#include <stdio.h>

// static void	free_env_node(t_env **env)
// {
// 	t_env	**head;

// 	head = get_env_list();
// 	if (!head || !*head || !env || !*env)
// 		return ;
// 	if ((*env)->prev)
// 		(*env)->prev->next = (*env)->next;
// 	else
// 		*head = (*env)->next;
// 	if ((*env)->next)
// 		(*env)->next->prev = (*env)->prev;
// 	free_env(env);
// }

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
		{
			printf("free key: %s\n", current->key);
			free(current->key);
		}
		if (current->value)
		{
			printf("free value: %s\n", current->value);
			free(current->value);
		}
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



// void	free_env_var(t_env **env, const char *key)
// {
// 	t_env *curr;

// 	if (!env || !*env || !key)
// 		return ;

// 	curr = *env;
// 	while (curr)
// 	{
// 		if (ft_strcmp(curr->key, key) == 0)
// 		{
// 			free_env_node(env);
// 			return ;
// 		}
// 		curr = curr->next;
// 	}
// }



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
