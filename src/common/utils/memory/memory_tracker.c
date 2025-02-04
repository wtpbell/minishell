/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   memory_tracker.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:37:32 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/02 23:27:21 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
// t_mem_container	*create_mem_context(void)
// {
// 	t_mem_container	*context;

// 	context = (t_mem_container *)malloc(sizeof(t_mem_container));
// 	if (!context)
// 		return (NULL);
// 	context->head = NULL;
// 	context->count = 0;
// 	return (context);
// }

// void	*context_malloc(t_mem_container *ctx, size_t size)
// {
// 	void			*ptr;
// 	t_mem_tracker	*new_tracker;

// 	if (!ctx)
// 		return (NULL);
// 	ptr = malloc(size);
// 	if (!ptr)
// 		return (NULL);
// 	new_tracker = (t_mem_tracker *)malloc(sizeof(t_mem_tracker));
// 	if (!new_tracker)
// 	{
// 		free(ptr);
// 		return (NULL);
// 	}
// 	new_tracker->ptr = ptr;
// 	new_tracker->next = ctx->head;
// 	ctx->head = new_tracker;
// 	ctx->count++;
// 	return (ptr);
// }


// void	context_free(t_mem_container *ctx, void *ptr)
// {
// 	t_mem_tracker	*curr;
// 	t_mem_tracker	*prev;

// 	if (!ctx || !ptr)
// 		return ;
// 	prev = NULL;
// 	curr = ctx->head;
// 	while (curr)
// 	{
// 		if (curr->ptr == ptr)
// 		{
// 			if (prev)
// 				prev->next = curr->next;
// 			else
// 				ctx->head = curr->next;
// 			free(curr);
// 			ctx->count--;
// 			break ;
// 		}
// 		prev = curr;
// 		curr = curr->next;
// 	}
// 	free(ptr);
// }


// void	cleanup_mem_context(t_mem_container *ctx)
// {
// 	t_mem_tracker	*curr;
// 	t_mem_tracker	*next;

// 	if (!ctx)
// 		return ;
// 	curr = ctx->head;
// 	while (curr)
// 	{
// 		next = curr->next;
// 		free(curr->ptr);
// 		free(curr);
// 		curr = next;
// 	}
// 	free(ctx);
// }

t_mem_container	*create_mem_context(void)
{
	t_mem_container	*ctx;

	ctx = (t_mem_container *)malloc(sizeof(t_mem_container));
	if (!ctx)
		return (NULL);
	ctx->head = NULL;
	ctx->count = 0;
	return (ctx);
}

// Allocate Memory and Track It
void	*context_malloc(t_mem_container *ctx, t_mem_context context_type, size_t size)
{
	void			*ptr;
	t_mem_tracker	*new_tracker;

	if (!ctx || size == 0)
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
	new_tracker->size = size;
	new_tracker->context = context_type;
	new_tracker->next = ctx->head;
	ctx->head = new_tracker;
	ctx->count++;
	return (ptr);
}
/*
	Use Selective Cleanup :
	- Shell runs continuously (like a real shell) and processes multiple commands.
	- Some parts of memory should be freed while keeping others.
	- Prevent memory leaks in a long-running shell
*/

void	context_free(t_mem_container *ctx, void *ptr, t_mem_context context_type)
{
	t_mem_tracker	*curr;
	t_mem_tracker	*prev;

	if (!ctx || !ptr)
		return ;
	prev = NULL;
	curr = ctx->head;
	while (curr)
	{
		if (curr->ptr == ptr && (curr->context == context_type || context_type == ALL))
		{
			if (prev)
				prev->next = curr->next;
			else
				ctx->head = curr->next;
			free(curr->ptr);
			free(curr);
			ctx->count--;
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	cleanup_mem_context(t_mem_container *ctx, t_mem_context context_type)
{
	t_mem_tracker	*curr;
	t_mem_tracker	*prev;
	t_mem_tracker	*next;

	curr = ctx->head;
	prev = NULL;
	if (!ctx)
		return;
	while (curr)
	{
		next = curr->next;
		if (curr->context == context_type)
		{
			free(curr->ptr);
			free(curr);
			if (prev)
				prev->next = next;
			else
				ctx->head = next;
			ctx->count--;
		}
		else
			prev = curr;
		curr = next;
	}
}

// Debug Function: Print All Allocated Memory
void	print_mem_tracker(const t_mem_container *ctx)
{
	t_mem_tracker	*curr;
	const char	*ctx_names[] = {"GENERAL", "LEXER", "PARSER", "EXECUTOR", "EXPANDER"};

	if (!ctx)
		return;
	curr = ctx->head;
	if (!curr)
	{
		printf("No memory allocations found.\n");
		return ;
	}
	printf("Memory Allocations:\n");
	while (curr)
	{
		if (curr->context >= 0 && curr->context < ALL)
			printf("PTR: %p | SIZE: %zu | CTX: %s\n", 
				curr->ptr, curr->size, ctx_names[curr->context]);
		else
			printf("PTR: %p | SIZE: %zu | CTX: INVALID\n", 
				curr->ptr, curr->size);
		curr = curr->next;
	}
}

void	debug_mem_context(const t_mem_container *ctx)
{
	printf("\n========== Memory Contexts Debug ==========\n");
	print_mem_tracker(ctx);
	printf("==========================================\n\n");
}
