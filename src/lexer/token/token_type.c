/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_type.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:25:10 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/13 09:36:44 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token_type	get_operator_type(char *input)
{
	if (!input || !*input)
		return (TOKEN_WORD);
	if (input[0] == '|' && input[1] == '|')
		return (TOKEN_OR);
	if (input[0] == '&' && input[1] == '&')
		return (TOKEN_AND);
	if (input[0] == '<' && input[1] == '<')
		return (TOKEN_HEREDOC);
	if (input[0] == '>' && input[1] == '>')
		return (TOKEN_APPEND);
	if (input[0] == '|')
		return (TOKEN_PIPE);
	if (input[0] == '<')
		return (TOKEN_REDIR_IN);
	if (input[0] == '>')
		return (TOKEN_REDIR_OUT);
	if (input[0] == '(')
		return (TOKEN_LPAREN);
	if (input[0] == ')')
		return (TOKEN_RPAREN);
	return (TOKEN_WORD);
}

int	get_operator_len(t_token_type type)
{
	if (type == TOKEN_OR || type == TOKEN_AND
		|| type == TOKEN_HEREDOC || type == TOKEN_APPEND)
		return (2);
	if (type == TOKEN_WORD)
		return (0);
	return (1);
}
