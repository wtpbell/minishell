/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 13:02:50 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/12 12:11:00 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "executor.h"

static t_ast_node	*parse_tokens_to_ast(t_token **tokens)
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
	if (*tokens)
	{
		set_exit_status(1);
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
		ft_putstr_fd(RED, STDERR_FILENO);
		ft_putendl_fd(get_syntax_error_msg(syntax_status), STDERR_FILENO);
		ft_putstr_fd(RESET, STDERR_FILENO);
		free_ast(root);
		return (NULL);
	}
	cmd_status = validate_command_syntax(root);
	if (cmd_status != VALID_SUCCESS)
	{
		ft_putstr_fd(RED, STDERR_FILENO);
		ft_putendl_fd(get_validation_error_msg(cmd_status), STDERR_FILENO);
		ft_putstr_fd(RESET, STDERR_FILENO);
		free_ast(root);
		return (NULL);
	}
	return (root);
}

t_ast_node	*parse(t_token *tokens)
{
	t_ast_node	*root;
	t_token		*current;

	if (!tokens || !validate_first_token(tokens))
		return (NULL);
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
