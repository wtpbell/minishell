/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal_utils1.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/14 17:04:59 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/14 17:19:44 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "executor.h"

volatile sig_atomic_t g_signal = SIG_NONE;

void	signal_set(t_signal_state state)
{
	g_signal |= state;
}

void	signal_clear(t_signal_state state)
{
	g_signal &= ~state;
}

int	signal_set(t_signal_state state)
{
	return (g_signal & state != 0);
}

void	signals_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
}

void	signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
}
