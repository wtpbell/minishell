/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_ast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/13 09:43:21 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/13 09:43:58 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "executor.h"

int	is_command_separator(t_token *token)
{
	return (token && (token->type == TOKEN_PIPE || token->type == TOKEN_AND
			|| token->type == TOKEN_OR));
}

t_ast_node	*parse_tokens_to_ast(t_token **tokens)
{
	t_ast_node	*root;
	t_token		*current;

	current = *tokens;
	root = parse_complete_bonus(tokens);
	if (!root)
	{
		if (current && is_redirection(current))
			handle_redirection_error_message(current);
		else
		{
			ft_putstr_fd(RED, STDERR_FILENO);
			ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
			ft_putstr_fd(RESET, STDERR_FILENO);
		}
		set_exit_status(2);
		return (NULL);
	}
	if (*tokens && !is_command_separator(*tokens))
	{
		set_exit_status(1);
		free_ast(root);
		return (NULL);
	}
	return (root);
}
