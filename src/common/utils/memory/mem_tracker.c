/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_tracker.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:37:32 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/23 12:50:03 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "minishell.h"
#include "executor.h"
#include <stdio.h>

/*
	It is a static array of linked lists, each representing a memory ctx.
	it returns a ptr to the linked list for the requested ctx.
*/
t_mem_tracker	**get_mem_list(void)
{
	static t_mem_tracker	*heap = NULL;

	return (&heap);
}

/* Free all memory allocated in the given context */
void	free_mem_context(void)
{
	t_mem_tracker	**head;

	head = get_mem_list();
	mem_lstclear(head, free);
}

/*
	Create a node to store the allocated ptr.
	Use Selective Cleanup :
	- Shell runs continuously (like a real shell) & processes multiple cmds.
	- Some parts of memory should be freed while keeping others.
	- Prevent memory leaks in a long-running shell
*/
void	*mem_alloc(size_t size)
{
	t_mem_tracker	**head;
	t_mem_tracker	*node;
	void			*ptr;

	head = get_mem_list();
	ptr = malloc(size);
	if (!ptr)
	{
		free_all_memory();
		perror("Memory allocation failure");
		exit(EXIT_FAILURE);
	}
	node = mem_lstnew(ptr);
	if (!node)
	{
		free(ptr);
		free_all_memory();
		perror("Memory allocation failure");
		exit(EXIT_FAILURE);
	}
	node->size = size;
	mem_lstadd_back(head, node);
	return (ptr);
}
