/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_type.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:25:10 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/12 15:41:26 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
** Return operator type (||, &&, <<, >>, |, <, >, (, ))
** Returns TOKEN_WORD if not applicable
*/
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
	if (input[0] == '*')
		return (TOKEN_WILDCARD);
	return (TOKEN_WORD);
}

/* Returns the length of the ** operator
   (2: ||,&&,<<,>> 1: |,<,>,() 0: plain word) */
int	get_operator_len(t_token_type type)
{
	if (type == TOKEN_OR || type == TOKEN_AND
		|| type == TOKEN_HEREDOC || type == TOKEN_APPEND)
		return (2);
	if (type == TOKEN_WORD)
		return (0);
	return (1);
}
