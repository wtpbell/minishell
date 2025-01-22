/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/22 11:00:14 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/22 11:00:14 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	get_exec_status(t_tree *tree)
{
	if (tree->type & (TOKEN_AND || TOKEN_OR))
		return exec_ctrl(tree);
	else if (tree->type & (TOKEN_REDIR_IN || TOKEN_REDIR_OUT))
		return exec_redir(tree);
	else if (tree->type & TOKEN_BLOCK)
		return exec_block(tree);
	else if (tree->type & TOKEN_PIPE)
		return exec_pipe(tree);
	else if (tree->type & TOKEN_EXEC)
		return exec_cmd(tree);
	return (EXIT_FAILURE);
}

void	executor(t_tree *tree)
{
	int	status;

	if (!tree)
		return ;
	status = get_exec_status(tree);
	set_exit_status(status);
}
