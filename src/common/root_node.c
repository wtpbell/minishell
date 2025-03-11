/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   root_node.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 13:23:24 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/11 15:22:23 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

t_ast_node	*get_root_node(t_ast_node *new_root)
{
	static t_ast_node	*root_node = NULL;

	if (new_root != NULL)
		root_node = new_root;
	return (root_node);
}
