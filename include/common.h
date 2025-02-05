/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   common.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 14:56:46 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/05 14:03:56 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "executor.h"

void	interrupt_from_keyboard(int sig);
void	signals_init(void);

#endif
