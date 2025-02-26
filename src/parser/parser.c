/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 13:02:50 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/26 21:16:19 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_valid_token_sequence(t_token *tokens)
{
	if (!tokens)
		return (0);
	if (!validate_parentheses(tokens))
	{
		ft_putendl_fd("minishell: syntax error: unmatched parentheses", 2);
		return (0);
	}
	return (1);
}

static t_ast_node	*parse_tokens_to_ast(t_token **tokens)
{
	t_ast_node	*root;

	root = parse_complete_bonus(tokens);
	if (!root)
		return (NULL);
	if (*tokens)
	{
		ft_putendl_fd("minishell: syntax error: unexpected token", 2);
		free_ast(root);
		return (NULL);
	}
	return (root);
}

static t_ast_node	*validate_ast(t_ast_node *root)
{
	t_syntax_error		syntax_status;
	t_cmd_valid_error	cmd_status;

	syntax_status = validate_syntax_tree(root);
	if (syntax_status != SYNTAX_OK)
	{
		ft_putendl_fd(get_syntax_error_msg(syntax_status), STDERR_FILENO);
		free_ast(root);
		return (NULL);
	}
	cmd_status = validate_command_syntax(root);
	if (cmd_status != VALID_SUCCESS)
	{
		ft_putendl_fd(get_validation_error_msg(cmd_status), STDERR_FILENO);
		free_ast(root);
		return (NULL);
	}
	return (root);
}

t_ast_node	*parse(t_token *tokens)
{
	t_ast_node	*root;
	t_token		*current;

	if (!is_valid_token_sequence(tokens))
		return (NULL);
	current = tokens;
	root = parse_tokens_to_ast(&current);
	if (!root)
		return (NULL);
	root = validate_ast(root);
	if (!root)
		return (NULL);
	root = optimize_ast(root);
	return (root);
}
