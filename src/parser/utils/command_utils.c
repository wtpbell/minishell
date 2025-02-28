/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/11 15:30:14 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/28 10:08:35 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_invalid_filename_char(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '&'
		|| c == ';' || c == '(' || c == ')');
}

int	is_valid_filename_token(t_token *token)
{
	return (token && (token->type == TOKEN_WORD
			|| token->type == TOKEN_WILDCARD));
}

int	is_valid_command_name(const char *cmd)
{
	int	i;

	if (!cmd || !*cmd)
		return (0);
	i = 0;
	while (cmd[i])
	{
		if (is_invalid_filename_char(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}
