/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 12:40:02 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/28 15:09:23 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "parser.h"

typedef struct s_mem_tracker
{
	void					*ptr;
	struct s_mem_tracker	*next;
}	t_mem_tracker;

typedef struct s_mem_context
{
	t_mem_tracker	*head;
	int				count;
}	t_mem_context;

#endif
