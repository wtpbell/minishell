/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/06 16:36:51 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/06 20:29:08 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "minishell.h"

t_mem_tracker	*mem_lstnew(void *ptr)
{
	t_mem_tracker	*newnode;

	newnode = (t_mem_tracker *)malloc(sizeof(t_mem_tracker));
	if (newnode == NULL)
		return (NULL);
	newnode->ptr = ptr;
	newnode->next = NULL;
	return (newnode);
}

bool	mem_lstclear(t_mem_tracker **lst, void (*del)(void *))
{
	t_mem_tracker	*curr;
	t_mem_tracker	*head;

	if (del == NULL || lst == NULL || *lst == NULL)
		return (false);
	head = *lst;
	curr = head;
	while (head != NULL)
	{
		head = head->next;
		del(curr->ptr);
		free(curr);
		curr = head;
	}
	*lst = NULL;
	return (true);
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

static t_mem_tracker	*mem_lstlast(t_mem_tracker *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

bool	mem_lstadd_back(t_mem_tracker **lst, t_mem_tracker *new_node)
{
	t_mem_tracker	*last;

	if (new_node == NULL || lst == NULL)
		return (false);
	if (*lst == NULL)
	{
		*lst = new_node;
		return (true);
	}
	last = mem_lstlast(*lst);
	last->next = new_node;
	return (true);
}
