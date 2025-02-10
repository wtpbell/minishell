/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   group_handler.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:55:35 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/10 10:19:39 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	print_current_token(t_token *token, const char *prefix)
{
	if (token)
		printf("\033[0;33m%s: type=%d, content='%s'\n\033[0m",
			prefix, token->type, token->content);
	else
		printf("\033[0;33m%s: NULL\n\033[0m", prefix);
}

static t_ast_node	*handle_logic_operation(t_token **token, t_ast_node *left)
{
	t_ast_node	*logic_node;
	t_ast_node	*right;

	logic_node = create_logic_node(token);
	if (!logic_node)
		return (NULL);
	if ((*token)->type == TOKEN_LPAREN)
		right = parse_group(token);
	else
		right = parse_pipeline(token);
	if (!right)
	{
		free_ast(logic_node);
		return (NULL);
	}
	logic_node->left = left;
	logic_node->right = right;
	return (logic_node);
}

static t_ast_node	*parse_command_sequence(t_token **token, t_token_type end_type)
{
	t_ast_node	*current;
	t_ast_node	*result;

	print_current_token(*token, "Parsing command sequence");
	if ((*token)->type == TOKEN_LPAREN)
		current = parse_group(token);
	else
	{
		current = parse_redirection(token);
		if (!current)
			current = parse_pipeline(token);
	}
	if (!current)
		return (NULL);
	while (*token && (*token)->type != end_type)
	{
		print_current_token(*token, "Processing sequence token");
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

t_ast_node	*create_subshell_node(void)
{
	t_ast_node	*node;

	node = create_ast_node(TOKEN_SUBSHELL);
	if (!node)
		return (NULL);
	node->is_subshell = 1;
	return (node);
}

t_ast_node	*parse_group(t_token **token)
{
	t_ast_node	*subshell_node;
	t_ast_node	*content;
	t_ast_node	*result;

	print_current_token(*token, "Entering parse_group");
	if (!token || !*token)
		return (NULL);
	if ((*token)->type != TOKEN_LPAREN)
		return (parse_command_sequence(token, TOKEN_EOF));
	subshell_node = create_subshell_node();
	if (!subshell_node)
		return (NULL);
	*token = (*token)->next;
	content = parse_command_sequence(token, TOKEN_RPAREN);
	if (!content)
	{
		free_ast(subshell_node);
		return (handle_group_error("invalid subshell syntax"));
	}
	subshell_node->left = content;
	if (!*token || (*token)->type != TOKEN_RPAREN)
	{
		free_ast(subshell_node);
		return (handle_group_error("missing closing parenthesis"));
	}
	print_current_token(*token, "Found closing parenthesis");
	*token = (*token)->next;
	if (*token && is_logic_operator(*token))
	{
		result = handle_logic_operation(token, subshell_node);
		if (!result)
		{
			free_ast(subshell_node);
			return (NULL);
		}
		return (result);
	}
	return (subshell_node);
}
