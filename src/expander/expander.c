/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/10 10:35:01 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/13 17:55:56 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"

void	expand_vars(t_ast_node *node)
{
	if (node->type == TOKEN_EXEC)
		return (expand_exec_vars(node));
	else
		return (expand_redir_vars(node->redirections));
}

void	expander(t_ast_node *node)
{
	expand_vars(node);
	// expand_wildcards(node);
}
