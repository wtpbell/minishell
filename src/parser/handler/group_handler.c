/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:55:35 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/05 14:52:45 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast_node	*handle_group_error(char *msg)
{
	ft_putstr_fd("minishell: syntax error: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (NULL);
}

static int	validate_subshell_end(t_token *token)
{
	if (!token)
		return (1);
	if (token->type == TOKEN_PIPE || token->type == TOKEN_AND
		|| token->type == TOKEN_OR)
		return (1);
	if (token->type == TOKEN_RPAREN && check_paren_balance(token))
		return (1);
	return (0);
}

t_ast_node	*parse_group(t_token **token)
{
	t_ast_node	*node;

	if (!token || !*token)
		return (NULL);
	if (!is_left_paren(*token))
		return (parse_logic(token));
	if (!check_paren_balance(*token))
		return (handle_group_error("unmatched parenthesis"));
	(*token) = (*token)->next;
	node = create_ast_node(TOKEN_SUBSHELL);
	if (!node)
		return (NULL);
	node->left = parse_logic(token);
	if (!node->left || !is_right_paren(*token))
	{
		free_ast(node);
		return (handle_group_error("invalid subshell syntax"));
	}
	if (!validate_subshell_end((*token)->next))
	{
		free_ast(node);
		return (handle_group_error("unexpected token after subshell"));
	}
	(*token) = (*token)->next;
	return (node);
}
