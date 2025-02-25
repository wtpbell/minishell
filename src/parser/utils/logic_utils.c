/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   logic_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/10 15:08:29 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/11 15:24:51 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_logic_operator(t_token *token)
{
	return (token && (token->type == TOKEN_AND
			|| token->type == TOKEN_OR));
}

t_ast_node	*create_logic_node(t_token **token)
{
	t_ast_node		*node;
	t_token_type	type;

	if (!token || !*token || !is_logic_operator(*token))
		return (NULL);
	type = (*token)->type;
	node = create_ast_node(type);
	if (!node)
		return (NULL);
	*token = (*token)->next;
	return (node);
}
