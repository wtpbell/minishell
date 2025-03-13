/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_validator.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/13 09:45:01 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/13 09:45:35 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*validate_ast(t_ast_node *root)
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
