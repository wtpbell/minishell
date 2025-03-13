/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/03 14:49:07 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/13 09:36:49 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_tokens(t_token *token)
{
	t_token	*next;

	if (!token)
		return ;
	next = token->next;
	if (token->content)
		free(token->content);
	free(token);
	free_tokens(next);
}

int	is_redirection(t_token *token)
{
	if (!token || !token->content)
		return (0);
	return (token && (token->type == TOKEN_REDIR_IN
			|| token->type == TOKEN_REDIR_OUT
			|| token->type == TOKEN_HEREDOC
			|| token->type == TOKEN_APPEND));
}
