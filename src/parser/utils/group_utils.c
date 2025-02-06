/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/06 14:49:20 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/06 16:34:04 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Check if the token is a left parenthesis */
int	is_left_paren(t_token *token)
{
	return (token && token->type == TOKEN_LPAREN);
}

/* Check if the token is a right parenthesis */
int	is_right_paren(t_token *token)
{
	return (token && token->type == TOKEN_RPAREN);
}

/* Check if the token is valid after a subshell */
int	is_valid_after_subshell(t_token *token)
{
	if (!token)
		return (1);
	return (token->type == TOKEN_PIPE || token->type == TOKEN_AND
		|| token->type == TOKEN_OR || token->type == TOKEN_REDIR_IN
		|| token->type == TOKEN_REDIR_OUT || token->type == TOKEN_HEREDOC
		|| token->type == TOKEN_APPEND || token->type == TOKEN_RPAREN
		|| !token);
}

/* Handle group error */
t_ast_node	*handle_group_error(char *msg)
{
	ft_putstr_fd("minishell: syntax error: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (NULL);
}

/* Check if the parentheses are balanced */
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
