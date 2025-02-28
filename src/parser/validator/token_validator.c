/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_validator.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/28 09:59:36 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/28 10:07:18 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "executor.h"

int	is_valid_token_sequence(t_token *tokens)
{
	if (!tokens)
		return (0);
	if (!validate_parentheses(tokens))
	{
		ft_putendl_fd("minishell: syntax error: unmatched parentheses",
			STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	validate_first_token(t_token *token)
{
	if (token->type == TOKEN_PIPE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token '|'",
			STDERR_FILENO);
		set_exit_status(2);
		return (0);
	}
	else if (token->type == TOKEN_AND)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token '&&'",
			STDERR_FILENO);
		set_exit_status(2);
		return (0);
	}
	else if (token->type == TOKEN_OR)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token '||'",
			STDERR_FILENO);
		set_exit_status(2);
		return (0);
	}
	return (1);
}
