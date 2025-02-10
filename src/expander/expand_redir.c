/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_redir.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/10 12:00:39 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/10 15:36:03 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	expand_redir(t_ast_node *node)
{
	char	**words;

	if (node->type == TOKEN_HEREDOC)
		return (expand_heredoc);
	words = expand_filenames(node->redirection);
}
