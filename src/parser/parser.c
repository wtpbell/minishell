/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 13:02:50 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/14 11:05:55 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast_node	*parse(t_token *tokens)
{
	t_ast_node	*root;
	t_token		*current;

	if (!tokens || !validate_first_token(tokens))
		return (NULL);
	if (!is_valid_token_sequence(tokens))
		return (NULL);
	current = tokens;
	root = parse_tokens_to_ast(&current);
	if (!root)
		return (NULL);
	root = validate_ast(root);
	if (!root)
		return (NULL);
	return (root);
}
