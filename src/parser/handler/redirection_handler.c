/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection_handler.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:55:07 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/05 15:05:41 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Check for redirect tokens (<, >, >>, <<) */
static int	is_redirection(t_token *token)
{
	if (!token || !token->content)
		return (0);
	return (token && (token->type == TOKEN_REDIR_IN
			|| token->type == TOKEN_REDIR_OUT
			|| token->type == TOKEN_HEREDOC
			|| token->type == TOKEN_APPEND));
}

/* Handling redirect syntax errors */
static t_ast_node	*handle_redirection_error(t_token **token)
{
	if (!*token || (*token)->type != TOKEN_WORD)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token",
			STDERR_FILENO);
		return (NULL);
	}
	return (create_ast_node(TOKEN_WORD));
}

/* Create a redirect node */
static t_ast_node	*create_redirection_node(t_token **token)
{
	t_ast_node		*node;
	t_token_type	type;

	if (!token || !*token || !(*token)->content)
		return (NULL);
	type = (*token)->type;
	*token = (*token)->next;
	node = create_ast_node(type);
	if (!node)
		return (NULL);
	if (!*token || (*token)->type != TOKEN_WORD)
	{
		free_ast(node);
		return (handle_redirection_error(token));
	}
	add_arg_to_node(node, (*token)->content);
	*token = (*token)->next;
	return (node);
}

/* Parses the entire redirect syntax */
t_ast_node	*parse_redirection(t_token **token)
{
	t_ast_node	*redir_node;
	t_ast_node	*cmd_node;

	if (!token || !*token || !(*token)->content)
		return (NULL);
	if (!is_redirection(*token))
		return (parse_command(token));
	redir_node = create_redirection_node(token);
	if (!redir_node)
		return (NULL);
	cmd_node = parse_command(token);
	if (!cmd_node)
	{
		redir_node->left = NULL;
		return (redir_node);
	}
	redir_node->left = cmd_node;
	return (redir_node);
}
