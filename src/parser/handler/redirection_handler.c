/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection_handler.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 21:55:07 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/14 16:00:05 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "executor.h"

void	set_redir_flags_and_fd(t_redir *redir, t_token_type type)
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

void	add_redirection(t_ast_node *node, t_token_type type, char *file,
				t_quote_type quote_type)
{
	t_redir	*new_redir;
	t_redir	*curr;

	if (!file)
		return ;
	new_redir = init_redir_node(type, file, quote_type);
	if (!new_redir)
		return ;
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

static void	add_args_to_cmd_node(t_ast_node *cmd_node, t_token **current)
{
	t_token	*temp;

	temp = *current;
	while (temp && (temp->type == TOKEN_WORD
			|| temp->type == TOKEN_WILDCARD))
	{
		add_arg_to_node(cmd_node, temp->content, temp->quote_type);
		temp = temp->next;
	}
	*current = temp;
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
		if (!current->next || !is_valid_filename_token(current->next))
			return (free_ast(cmd_node),*token = NULL, set_exit_status(2), NULL);
		add_redirection(cmd_node, current->type, current->next->content,
			current->next->quote_type);
		current = current->next->next;
	}
	if (current && (current->type == TOKEN_WORD
			|| current->type == TOKEN_WILDCARD))
		add_args_to_cmd_node(cmd_node, &current);
	*token = current;
	return (cmd_node);
}
