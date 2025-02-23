/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_free.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/23 12:38:14 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/23 12:38:56 by bewong        ########   odam.nl         */
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
		free_alloc((*env)->key);
		free_alloc((*env)->value);
		free_alloc(*env);
		*env = tmp;
	}
	*env = NULL;
}

/* Iterate over all memory contexts and free all */
void	free_all_memory(void)
{
	t_mem_tracker	**head;

	head = get_mem_list();
	mem_lstclear(head, free);
}

/* 
	Loop through the specific ctx memory list.
	If the ptr is found, free it and return.
*/
void	free_alloc(void *ptr)
{
	t_mem_tracker	**head;
	t_mem_tracker	*cur;

	head = get_mem_list();
	cur = *head;
	while (cur)
	{
		if (cur->ptr == ptr)
		{
			mem_lstdelone(head, cur);
			return ;
		}
		cur = cur->next;
	}
}

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		free_alloc(tab[i++]);
	free_alloc(tab);
}
