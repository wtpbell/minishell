/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/03 14:49:07 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/03 15:01:28 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Free the tokens */
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
