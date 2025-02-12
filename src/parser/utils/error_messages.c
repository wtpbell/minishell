/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_messages.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/29 12:32:49 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/29 12:49:02 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Return the error message string corresponding to each error type
** Define the message to be shown to the user for each error type */
char	*get_validation_error_msg(t_cmd_valid_error error)
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

char	*get_syntax_error_msg(t_syntax_error error)
{
	static char	*messages[7];

	messages[SYNTAX_OK] = "Success";
	messages[SYNTAX_UNEXPECTED_TOKEN]
		= "Syntax error: Unexpected token";
	messages[SYNTAX_MISSING_TOKEN]
		= "Syntax error: Missing token";
	messages[SYNTAX_INVALID_COMBINATION]
		= "Syntax error: Invalid combination of operators";
	messages[SYNTAX_UNMATCHED_PARENTHESES]
		= "Syntax error: Unmatched parentheses";
	messages[SYNTAX_INVALID_SEQUENCE]
		= "Syntax error: Invalid operator sequence";
	messages[SYNTAX_INVALID_SUBSHELL]
		= "Syntax error: Invalid subshell command";
	return (messages[error]);
}
