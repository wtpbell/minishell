/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sequence_handler.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/10 15:10:34 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/12 09:23:14 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Parse command sequence */
t_ast_node	*parse_command_sequence(t_token **token, t_token_type end_type)
{
	t_ast_node	*current;
	t_ast_node	*result;

	if ((*token)->type == TOKEN_LPAREN)
		current = parse_group(token);
	else
	{
		current = parse_redirection(token);
		if (!current)
		{
			current = parse_pipeline(token);
			if (!current)
				return (NULL);
		}
	}
	if (!current)
		return (NULL);
	while (*token && (*token)->type != end_type)
	{
		if (!is_logic_operator(*token))
			break ;
		result = handle_logic_operation(token, current);
		if (!result)
		{
			free_ast(current);
			return (NULL);
		}
		current = result;
	}
	return (current);
}
