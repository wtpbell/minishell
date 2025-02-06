/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   group_utils.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <spyun@student.codam.nl>                +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/02/06 14:49:20 by spyun          #+#    #+#                */
/*   Updated: 2025/02/06 14:49:22 by spyun          ########   odam.nl        */
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

int	check_paren_balance(t_token *start)
{
	t_token	*current;
	int		count;

	count = 0;
	current = start;
	while (current)
	{
		if (current->type == TOKEN_LPAREN)
			count++;
		else if (current->type == TOKEN_RPAREN)
		{
			count--;
			if (count < 0)
				return (0);
		}
		current = current->next;
	}
	return (count == 0);
}
