/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:40:02 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/02 23:16:19 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "parser.h"

// typedef struct s_mem_tracker
// {
// 	void					*ptr;
// 	struct s_mem_tracker	*next;
// }	t_mem_tracker;

// typedef struct s_mem_context
// {
// 	t_mem_tracker	*head;
// 	int				count;
// }	t_mem_context;

typedef enum e_mem_context
{
	LEXER,
	PARSER,
	EXECUTOR,
	EXPANDER,
	GENERAL,
	ALL
} t_mem_context;

typedef struct s_mem_tracker
{
	void					*ptr;
	t_mem_context			context;
	size_t					size;
	struct s_mem_tracker	*next;
}	t_mem_tracker;

typedef struct s_mem_container
{
	t_mem_tracker	*head;
	int				count;
} t_mem_container;

#endif
