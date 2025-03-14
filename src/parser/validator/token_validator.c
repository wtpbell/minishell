/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_validator.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/28 09:59:36 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/14 14:24:16 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "executor.h"

static int	is_valid_after_rparen(t_token_type type)
{
	return (type == TOKEN_AND || type == TOKEN_OR
		|| type == TOKEN_PIPE || type == TOKEN_RPAREN);
}

static int	check_consecutive_paren(t_token *tokens)
{
	t_token	*curr;
	int		last_was_rparen;

	curr = tokens;
	last_was_rparen = 0;
	while (curr)
	{
		if (last_was_rparen && !is_valid_after_rparen(curr->type))
		{
			print_token_error(curr->content);
			return (0);
		}
		if (curr->type == TOKEN_RPAREN)
			last_was_rparen = 1;
		else if (curr->type == TOKEN_AND || curr->type == TOKEN_OR
			|| curr->type == TOKEN_PIPE)
			last_was_rparen = 0;
		curr = curr->next;
	}
	return (1);
}

int	is_valid_token_sequence(t_token *tokens)
{
	if (!tokens)
		return (0);
	if (!validate_parentheses(tokens))
	{
		print_paren_error();
		return (0);
	}
	return (check_consecutive_paren(tokens));
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
