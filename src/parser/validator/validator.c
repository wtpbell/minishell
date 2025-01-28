/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validator.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 10:18:14 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/27 12:15:58 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	is_invalid_filename_char(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '&'
		|| c == ';' || c == '(' || c == ')');
}

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

t_valid_error	validate_redirection_syntax(t_redirection *redirs)
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

t_valid_error	validate_command_syntax(t_ast_node *node)
{
	t_valid_error	redir_status;

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

char	*get_validation_error_msg(t_valid_error error)
{
	static char	*messages[6];

	messages[VALID_SUCCESS] = "Success";
	messages[VALID_EMPTY_CMD] = "Command cannot be empty";
	messages[VALID_INVALID_REDIR] = "Invalid redirection";
	messages[VALID_MISSING_FILENAME] = "Missing filename after redirection";
	messages[VALID_SYNTAX_ERROR] = "Syntax error in command";
	messages[VALID_TOO_MANY_ARGS] = "Too many arguments";
	return (messages[error]);
}
