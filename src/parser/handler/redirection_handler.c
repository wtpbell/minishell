/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection_handler.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:55:07 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/27 10:39:53 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

static void	set_redir_flags_and_fd(t_redir *redir, t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
	{
		redir->flags = O_RDONLY;
		redir->fd = 0;
	}
	else if (type == TOKEN_REDIR_OUT)
	{
		redir->flags = O_WRONLY | O_CREAT | O_TRUNC;
		redir->fd = 1;
	}
	else if (type == TOKEN_APPEND)
	{
		redir->flags = O_WRONLY | O_CREAT | O_APPEND;
		redir->fd = 1;
	}
	else if (type == TOKEN_HEREDOC)
	{
		redir->flags = O_RDONLY;
		redir->fd = 0;
	}
}

void	add_redirection(t_ast_node *node, t_token_type type, char *file)
{
	t_redir	*new_redir;
	t_redir	*curr;

	if (!file)
		return ;
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = type;
	new_redir->file = ft_strdup(file);
	new_redir->next = NULL;
	set_redir_flags_and_fd(new_redir, type);
	if (!node->redirections)
		node->redirections = new_redir;
	else
	{
		curr = node->redirections;
		while (curr->next)
			curr = curr->next;
		curr->next = new_redir;
	}
}

t_ast_node	*parse_redirection(t_token **token)
{
	t_ast_node	*cmd_node;
	t_token		*current;

	if (!token || !*token || !is_redirection(*token))
		return (NULL);
	cmd_node = create_ast_node(TOKEN_WORD);
	if (!cmd_node)
		return (NULL);
	current = *token;
	while (current && is_redirection(current))
	{
		if (!current->next || current->next->type != TOKEN_WORD)
			return (free_ast(cmd_node), handle_redirection_error(token));
		add_redirection(cmd_node, current->type, current->next->content);
		current = current->next->next;
	}
	while (current && current->type == TOKEN_WORD)
	{
		add_arg_to_node(cmd_node, current->content, current->quote_type);
		current = current->next;
	}
	*token = current;
	return (cmd_node);
}
