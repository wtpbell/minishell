/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/06 16:36:51 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/06 17:45:27 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "minishell.h"

t_mem_tracker	*mem_lstnew(void *ptr)
{
	t_mem_tracker	*new_node;

	new_node = malloc(sizeof(t_mem_tracker));
	if (!new_node)
		return (NULL);
	new_node->ptr = ptr;
	new_node->next = NULL;
	return (new_node);
}

void	mem_lstclear(t_mem_tracker **lst, void (*del)(void *))
{
	t_mem_tracker	*temp;
	t_mem_tracker	*current;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		temp = current->next;
		if (del)
			del(current->ptr);
		free(current);
		current = temp;
	}
	*lst = NULL;
}


void	mem_lstdelone(t_mem_tracker **head, t_mem_tracker *target)
{
	t_mem_tracker	*cur = *head;
	t_mem_tracker	*prev = NULL;

	if (!head || !*head || !target)
		return ;
	while (cur)
	{
		if (cur == target)
		{
			if (prev)
				prev->next = cur->next;
			else
				*head = cur->next;
			free(cur->ptr);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

void	mem_lstadd_back(t_mem_tracker **lst, t_mem_tracker *new_node)
{
	t_mem_tracker	*temp;

	if (!lst || !new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}
