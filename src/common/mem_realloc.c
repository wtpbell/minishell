/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_realloc.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/03 11:02:35 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/04 21:28:37 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	*mem_realloc(void *ptr, size_t new_size, size_t old_size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_size > new_size)
		old_size = new_size;
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}
