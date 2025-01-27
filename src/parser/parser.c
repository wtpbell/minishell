/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 13:02:50 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/24 09:21:08 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Generate AST from token list (parsing starting point) */
t_ast_node	*parse(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	return (parse_pipeline(&tokens));
}

/* todo -> argument count */
