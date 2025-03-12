/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_validator.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/28 09:59:36 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/12 16:17:13 by bewong        ########   odam.nl         */
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
		ft_putstr_fd(RED, STDERR_FILENO);
		ft_putendl_fd("minishell: syntax error: unmatched parentheses",
			STDERR_FILENO);
		ft_putstr_fd(RESET, STDERR_FILENO);
		return (0);
	}
	return (1);
}

static void	print_syntax_error(char *token_str)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd("minishell: syntax error near unexpected token '", \
				STDERR_FILENO);
	ft_putstr_fd(token_str, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
	set_exit_status(2);
}

int	validate_first_token(t_token *token)
{
	if (token->type == TOKEN_PIPE)
		print_syntax_error("|");
	else if (token->type == TOKEN_AND)
		print_syntax_error("&&");
	else if (token->type == TOKEN_OR)
		print_syntax_error("||");
	else
		return (1);
	return (0);
}
