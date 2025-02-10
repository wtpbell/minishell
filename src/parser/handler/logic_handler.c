/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   logic_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:55:52 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/10 09:25:32 by spyun         ########   odam.nl         */
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

t_ast_node	*handle_logic_sequence(t_token **token, t_ast_node *left)
{
	t_ast_node	*logic_node;
	t_ast_node	*right;

	if (!token || !*token || !is_logic_operator(*token))
		return (left);
	logic_node = create_logic_node(token);
	if (!logic_node)
	{
		free_ast(left);
		return (handle_logic_error());
	}
	right = parse_pipeline(token);
	if (!right)
	{
		free_ast(left);
		free_ast(logic_node);
		return (handle_logic_error());
	}
	logic_node->left = left;
	logic_node->right = right;
	return (logic_node);
}

t_ast_node	*parse_logic(t_token **token)
{
	t_ast_node	*left;
	t_ast_node	*processed;

	left = parse_pipeline(token);
	if (!left || !*token)
		return (left);
	while (*token && is_logic_operator(*token))
	{
		processed = handle_logic_sequence(token, left);
		if (!processed)
			return (NULL);
		left = processed;
		if (!*token)
			break ;
	}
	return (left);
}

t_ast_node	*parse_complete_bonus(t_token **token)
{
	if (!token || !*token)
		return (NULL);
	return (parse_group(token));
}
