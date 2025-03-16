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
#include "executor.h"
#include "common.h"

void	set_exit_status(int status)
{
	char	*status_;

	if (signal_is_set(SIG_RECEIVED_TERM))
		status_ = 0;
	status_ = ft_itoa(status);
	if (status_)
	{
		set_env(*get_env_list(), "?", status_);
		free(status_);
	}
}

int	get_exit_status(void)
{
	char	*status_str;

	status_str = get_env_value(*get_env_list(), "?");
	if (!status_str)
		return (0);
	return (ft_atoi(status_str));
}
