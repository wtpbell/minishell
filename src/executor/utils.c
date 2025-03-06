/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 17:22:19 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/06 16:04:10 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "common.h"
#include "env.h"

void	cleanup_heredocs(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC && redir->heredoc_file)
			unlink(redir->heredoc_file);
		redir = redir->next;
	}
}
