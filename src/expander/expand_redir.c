/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_redir.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/10 12:00:39 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/11 10:55:26 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	expand_redir(t_ast_node *node)
{
	char	**words;

	if (node->type == TOKEN_HEREDOC)
		return (expand_heredoc(node->redirection));
	words = expand_filenames(node->redirection);
}
