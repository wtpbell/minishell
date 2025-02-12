/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_validator.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 10:18:14 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/30 09:42:47 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Checks for prohibited special characters in the filename.
** Invalid if it contains characters
such as ‘<’, ‘>’, ‘|’, ‘&’, ‘;’, ‘(’, ‘)’ */
static int	is_invalid_filename_char(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '&'
		|| c == ';' || c == '(' || c == ')');
}

/* Checks if the command name is valid
** invalid if it is an empty string or contains special characters */
int	is_valid_command_name(const char *cmd)
{
	int	i;

	if (!cmd || !*cmd)
		return (0);
	i = 0;
	while (cmd[i])
	{
		if (is_invalid_filename_char(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}

/* Validate redirect syntax
** Return error if no filename or invalid filename */
t_cmd_valid_error	validate_redirection_syntax(t_redirection *redirs)
{
	t_redirection	*curr;

	curr = redirs;
	while (curr)
	{
		if (!curr->file)
			return (VALID_MISSING_FILENAME);
		if (!is_valid_command_name(curr->file))
			return (VALID_INVALID_REDIR);
		curr = curr->next;
	}
	return (VALID_SUCCESS);
}

/* Complete validation of the command syntax.
** Check for empty commands, bad syntax,
too many arguments, invalid redirects, etc */
t_cmd_valid_error	validate_command_syntax(t_ast_node *node)
{
	t_cmd_valid_error	redir_status;

	if (!node)
		return (VALID_EMPTY_CMD);
	if (node->type == TOKEN_WORD)
	{
		if (!node->args || !node->args[0])
			return (VALID_EMPTY_CMD);
		if (!is_valid_command_name(node->args[0]))
			return (VALID_SYNTAX_ERROR);
		if (node->argc > 1024)
			return (VALID_TOO_MANY_ARGS);
		if (node->redirections)
		{
			redir_status = validate_redirection_syntax(node->redirections);
			if (redir_status != VALID_SUCCESS)
				return (redir_status);
		}
	}
	return (VALID_SUCCESS);
}
