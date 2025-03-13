/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sequence_handler.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/10 15:10:34 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/13 09:49:14 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast_node	*init_sequence(t_token **token)
{
	t_ast_node	*current;

	if ((*token)->type == TOKEN_LPAREN)
		current = parse_group(token);
	else
	{
		current = parse_redirection(token);
		if (!current)
			current = parse_pipeline(token);
	}
	return (current);
}

static t_ast_node	*handle_pipe_if_needed(t_token **token, t_ast_node *current)
{
	t_ast_node	*result;

	if (*token && (*token)->type == TOKEN_PIPE)
	{
		result = handle_pipe_right(token, current);
		if (!result)
			return (NULL);
		return (result);
	}
	return (current);
}

/* Parse command sequence */
t_ast_node	*parse_command_sequence(t_token **token, t_token_type end_type)
{
	t_ast_node	*current;
	t_ast_node	*result;

	current = init_sequence(token);
	if (!current)
		return (NULL);
	current = handle_pipe_if_needed(token, current);
	if (!current)
		return (NULL);
	while (*token && (*token)->type != end_type)
	{
		if (!is_logic_operator(*token))
			break ;
		result = handle_logic_operation(token, current);
		if (!result)
			return (NULL);
		current = result;
	}
	return (current);
}
