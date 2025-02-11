/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redir_validator.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/29 09:13:33 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/11 14:50:05 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Validate redirection syntax */
t_syntax_error	validate_redir_syntax(t_ast_node *node)
{
	t_redirection	*redir;

	if (!node)
		return (SYNTAX_INVALID_COMBINATION);
	redir = node->redirections;
	while (redir)
	{
		if (!redir->file)
			return (SYNTAX_INVALID_COMBINATION);
		redir = redir->next;
	}
	return (SYNTAX_OK);
}
