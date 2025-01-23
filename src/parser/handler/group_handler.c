/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:55:35 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/23 19:47:35 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*  Make sure the token is a left parenthesis */
static int	is_left_paren(t_token *token)
{
	return (token && token->type == TOKEN_LPAREN);
}

/*  Make sure the token is a right parenthesis */
static int	is_right_paren(t_token *token)
{
	return (token && token->type == TOKEN_RPAREN);
}

/* Handle syntax errors related to parentheses */
static t_ast_node	*handle_group_error(char *msg)
{
	ft_putstr_fd("minishell: syntax error: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (NULL);
}
/* Parses the parenthesised expression to create an AST node */
t_ast_node	*parse_group(t_token **token)
{
	t_ast_node	*node;

	if (!token || !*token)
		return (NULL);
	if (!is_left_paren(*token))
		return (parse_logic(token));
	*token = (*token)->next;
	if (!*token)
		return (handle_group_error("unexpected end after '('"));
	node = parse_logic(token);
	if (!node)
		return (NULL);
	if (!*token || !is_right_paren(*token))
	{
		free_ast(node);
		return (handle_group_error("missing closing parenthesis"));
	}
	*token = (*token)->next;
	return (node);
}
