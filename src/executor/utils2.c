/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/31 16:48:58 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/31 18:06:19 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"

void	append_cwd(t_ast_node *node)
{
	char	*cwd;
	char	*tmp;
	char	*tmp2;

	cwd = getcwd(node->env, PATH_MAX);
	if (!cwd)
		return (error("cd", NULL), EXIT_FAILURE);
	
}

/*
	check_cmd() handles cmd resolution
	1. No PATH and not an absolute/relative command
	2. Not an absolute/relative
	3. Absolute/relative path
*/
int	check_cmd(t_ast_node *node)
{
	int status_;

	status_ = 0;
	if (get_env_value(node->env, "PATH") == NULL && node->args[0][0] != '/'
			&& node->args[0][0] != '.')
		append_cwd(node);
	if (node->args[0][0] != '/' && node->args[0][0] != '.')
		status_ = exec_path(node);
	else
		status_ = exec(node);
	return (status_);
}
