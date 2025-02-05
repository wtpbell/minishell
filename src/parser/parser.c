/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 13:02:50 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/05 14:45:07 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse(t_token *tokens)
{
	t_ast_node			*root;
	t_syntax_error		syntax_status;
	t_cmd_valid_error	cmd_status;

	if (!tokens)
		return (NULL);
	root = parse_complete_bonus(&tokens);
	if (!root)
		return (NULL);
	syntax_status = validate_syntax_tree(root);
	if (syntax_status != SYNTAX_OK)
	{
		ft_putendl_fd(get_syntax_error_msg(syntax_status), STDERR_FILENO);
		free_ast(root);
		return (NULL);
	}
	cmd_status = validate_command_syntax(root);
	if (cmd_status != VALID_SUCCESS)
	{
		ft_putendl_fd(get_validation_error_msg(cmd_status), STDERR_FILENO);
		free_ast(root);
		return (NULL);
	}
	root = optimize_ast(root);
	return (root);
}
