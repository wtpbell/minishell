/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_realloc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/03 11:02:35 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/03 11:07:44 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	*mem_realloc(void *ptr, size_t new_size, size_t old_size)
{
	void	*new_ptr;

	if (!ptr)
		return (mem_alloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = mem_alloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_size > new_size)
		old_size = new_size;
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}
