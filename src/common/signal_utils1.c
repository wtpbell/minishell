/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_utils1.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 17:04:59 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/15 21:11:32 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "executor.h"

volatile sig_atomic_t	g_signal = SIG_NONE;

void	signal_set(t_signal_state state)
{
	g_signal |= state;
}

void	signal_clear_all(void)
{
	g_signal = SIG_NONE;
}

int	signal_is_set(t_signal_state state)
{
	return (g_signal & state);
}
