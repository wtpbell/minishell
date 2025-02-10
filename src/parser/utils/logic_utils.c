/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   logic_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/10 15:08:29 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/10 15:18:37 by spyun         ########   odam.nl         */
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

t_ast_node	*handle_logic_error(void)
{
	ft_putendl_fd("minishell: syntax error near unexpected token",
		STDERR_FILENO);
	return (NULL);
}
