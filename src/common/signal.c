/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 14:41:36 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/31 16:40:24 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "executor.h"
#include <unistd.h>

void	interrupt_from_keyboard(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	set_exit_status(1);
}
