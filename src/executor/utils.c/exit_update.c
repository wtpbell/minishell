/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_update.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/22 17:42:30 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/22 17:42:30 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"


int get_exit_status(void)
{
	return (g_exit_status);
}
