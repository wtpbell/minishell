/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:55:35 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/05 14:52:45 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Make sure the token is a left parenthesis */
static int	is_left_paren(t_token *token)
{
	return (token && token->type == TOKEN_LPAREN);
}

/* Make sure the token is a right parenthesis */
static int	is_right_paren(t_token *token)
{
	return (token && token->type == TOKEN_RPAREN);
}

/* Handle syntax errors related to parentheses */
static t_ast_node	*handle_group_error(char *msg)
{
	ft_putstr_fd("minishell: syntax error: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (NULL);
}

static int	validate_subshell(t_token *token)
{
	int		paren_count;
	t_token	*current;

	paren_count = 1;
	current = token;
	while (current)
	{
		if (current->type == TOKEN_LPAREN)
			paren_count++;
		else if (current->type == TOKEN_RPAREN)
		{
			paren_count--;
			if (paren_count == 0)
				return (1);
		}
		current = current->next;
	}
	return (0);
}

static t_ast_node	*create_subshell_node(void)
{
	t_ast_node	*node;

	node = create_ast_node(TOKEN_SUBSHELL);
	if (!node)
		return (NULL);
	node->is_subshell = 1;
	return (node);
}

/* Parses the parenthesised expression to create an AST node */
t_ast_node	*parse_group(t_token **token)
{
	t_ast_node	*node;

	if (!token || !*token)
		return (NULL);
	if (!is_left_paren(*token))
		return (parse_logic(token));
	if (!validate_subshell((*token)->next))
		return (handle_group_error("unmatched parentheses"));
	(*token)++;
	node = create_subshell_node();
	if (!node)
		return (NULL);
	node->left = parse_logic(token);
	if (!node->left || !*token || !is_right_paren(*token))
	{
		free_ast(node);
		return (handle_group_error("invalid subshell syntax"));
	}
	(*token)++;
	return (node);
}
