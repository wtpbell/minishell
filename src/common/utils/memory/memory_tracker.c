/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memory_tracker.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:37:32 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/10 17:41:42 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "common.h"
#include "minishell.h"
#include <stdio.h>

/*
	It is a static array of linked lists, each representing a memory ctx.
	it returns a ptr to the linked list for the requested ctx.
*/
static t_mem_tracker	**get_mem_list(t_mem_context ctx)
{
	static	t_mem_tracker	*heap[ALL + 1];
	return (&heap[ctx]);
}

/* Iterate over all memory contexts and free all */
void	free_all_memory(void)
{
	int				i;
	t_mem_tracker	**head;

	i = -1;
	while (++i < ALL)
	{
		head = get_mem_list((t_mem_context)i);
		mem_lstclear(head, free);
	}
}

/* 
	Loop through the specific ctx memory list.
	If the ptr is found, free it and return.
*/
void	free_alloc(void *ptr, t_mem_context ctx)
{
	t_mem_tracker	**head;
	t_mem_tracker	*cur;

	head = get_mem_list(ctx);
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

/* Free all memory allocated in the given context */
void	free_mem_context(t_mem_context ctx)
{
	t_mem_tracker	**head;
	
	head = get_mem_list(ctx);
	mem_lstclear(head, free);
}

/*
	Create a node to store the allocated ptr.
	Use Selective Cleanup :
	- Shell runs continuously (like a real shell) and processes multiple commands.
	- Some parts of memory should be freed while keeping others.
	- Prevent memory leaks in a long-running shell
*/
void	*mem_alloc(size_t size, t_mem_context ctx)
{
	t_mem_tracker	**head;
	t_mem_tracker	*node;
	void			*ptr;

	head = get_mem_list(ctx);
	ptr = malloc(size);
	if (!ptr)
	{
		free_all_memory();
		perror("Memory allocation failure");
		exit(EXIT_FAILURE);
	}
	node =	mem_lstnew(ptr);
	if (!node)
	{
		free_all_memory();
		perror("Memory allocation failure");
		exit(EXIT_FAILURE);
	}
	node->size = size;
	mem_lstadd_back(head, node);
	return (ptr);
}


void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		free_alloc(tab[i++], GENERAL);
	free_alloc(tab, GENERAL);
}
