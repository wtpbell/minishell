/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memory_tracker.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:37:32 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/28 15:15:12 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_mem_context	*create_mem_context(void)
{
	t_mem_context	*context;

	context = (t_mem_context *)malloc(sizeof(t_mem_context));
	if (!context)
		return (NULL);
	context->head = NULL;
	context->count = 0;
	return (context);
}

void	*context_malloc(t_mem_context *ctx, size_t size)
{
	void			*ptr;
	t_mem_tracker	*new_tracker;

	if (!ctx)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_tracker = (t_mem_tracker *)malloc(sizeof(t_mem_tracker));
	if (!new_tracker)
	{
		free(ptr);
		return (NULL);
	}
	new_tracker->ptr = ptr;
	new_tracker->next = ctx->head;
	ctx->head = new_tracker;
	ctx->count++;
	return (ptr);
}

void	context_free(t_mem_context *ctx, void *ptr)
{
	t_mem_tracker	*curr;
	t_mem_tracker	*prev;

	if (!ctx || !ptr)
		return ;
	prev = NULL;
	curr = ctx->head;
	while (curr)
	{
		if (curr->ptr = ptr)
		{
			if (prev)
				prev->next = curr->next;
			else
				ctx->head = curr->next;
			free(curr);
			ctx->count--;
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	free(ptr);
}

void cleanup_mem_context(t_mem_context *ctx)
{
	t_mem_tracker	*curr;
	t_mem_tracker	*next;

	if (!ctx)
		return ;
	curr = ctx->head;
	while (curr)
	{
		next = curr->next;
		free(curr->ptr);
		free(curr);
		curr = next;
	}
	free(ctx);
}
