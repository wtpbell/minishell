/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_redirection_handler.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/05 17:53:00 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/15 19:39:17 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	process_redirection(t_ast_node *cmd_node, t_token **current)
{
	if (!*current || !(*current)->next || (*current)->next->type != TOKEN_WORD)
		return ;
	add_redirection(cmd_node, (*current)->type, (*current)->next->content,
		(*current)->next->quote_type);
	*current = (*current)->next->next;
}

static int	check_redirection_target(t_token *current, t_ast_node *cmd_node)
{
	if (!current->next || current->next->type != TOKEN_WORD)
	{
		free_ast(cmd_node);
		return (0);
	}
	return (1);
}

static void	process_token_content(t_ast_node *cmd_node, t_token **current,
		int *has_command)
{
	if (is_redirection(*current))
	{
		process_redirection(cmd_node, current);
	}
	else
	{
		*has_command = 1;
		add_arg_to_node(cmd_node, (*current)->content, (*current)->quote_type);
		*current = (*current)->next;
	}
}

t_ast_node	*handle_pipe_redirection(t_token **token)
{
	t_ast_node	*cmd_node;
	t_token		*current;
	int			has_command;

	cmd_node = create_ast_node(TOKEN_WORD);
	if (!cmd_node)
		return (NULL);
	current = *token;
	has_command = 0;
	while (current && (is_redirection(current) || current->type == TOKEN_WORD
			|| current->type == TOKEN_WILDCARD))
	{
		if (is_redirection(current) && !check_redirection_target(current,
				cmd_node))
			return (*token = NULL, NULL);
		process_token_content(cmd_node, &current, &has_command);
	}
	if (!has_command && !cmd_node->redirections)
		return (free_ast(cmd_node), NULL);
	*token = current;
	return (cmd_node);
}
