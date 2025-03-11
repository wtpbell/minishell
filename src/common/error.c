/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/23 00:39:29 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/03 12:20:26 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include "executor.h"
#include <stdio.h>
#include <unistd.h>

void	error(char *word, char *msg)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd(SHELL_ERROR, STDERR_FILENO);
	if (msg)
	{
		ft_putstr_fd(word, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(word, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	ft_putstr_fd(RESET, STDERR_FILENO);
	set_exit_status(EXIT_FAILURE);
}

void	error_heredoc(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited \
		by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
	set_exit_status(0);
	return ;
}
