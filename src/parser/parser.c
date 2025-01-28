/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 13:02:50 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/28 15:16:56 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Generate AST from token list (parsing starting point) */
t_ast_node	*parse(t_token *tokens)
{
	t_ast_node			*root;
	t_cmd_valid_error	status;

	if (!tokens)
		return (NULL);
	root = parse_pipeline(&tokens);
	if (!root)
		return (NULL);
	status = validate_command_syntax(root);
	if (status != VALID_SUCCESS)
	{
		ft_putendl_fd(get_validation_error_msg(status), STDERR_FILENO);
		free_ast(root);
		return (NULL);
	}
	return (root);
}

