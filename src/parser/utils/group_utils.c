/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/06 14:49:20 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/13 09:38:44 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_left_paren(t_token *token)
{
	return (token && token->type == TOKEN_LPAREN);
}

int	is_right_paren(t_token *token)
{
	return (token && token->type == TOKEN_RPAREN);
}

int	is_valid_after_subshell(t_token *token)
{
	if (!token)
		return (1);
	return (token->type == TOKEN_PIPE || token->type == TOKEN_AND
		|| token->type == TOKEN_OR || token->type == TOKEN_REDIR_IN
		|| token->type == TOKEN_REDIR_OUT || token->type == TOKEN_HEREDOC
		|| token->type == TOKEN_APPEND || token->type == TOKEN_RPAREN
		|| !token);
}
