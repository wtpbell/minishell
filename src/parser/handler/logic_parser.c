/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   logic_parser.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 22:16:54 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/04 20:49:35 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Logical operator sequencing and AST configuration */
t_ast_node	*handle_logic_sequence(t_token **token, t_ast_node *left)
{
	t_ast_node	*logic_node;
	t_ast_node	*right;

	if (!token || !*token || !is_logic_operator(*token))
		return (left);
	logic_node = create_logic_node(token);
	if (!logic_node)
	{
		free_ast(left);
		return (handle_logic_error());
	}
	right = parse_pipeline(token);
	if (!right)
	{
		free_ast(left);
		free_ast(logic_node);
		return (handle_logic_error());
	}
	logic_node->left = left;
	logic_node->right = right;
	return (logic_node);
}

/* Bonus part: parsing the entire syntax, including parentheses */
t_ast_node	*parse_complete_bonus(t_token **token)
{
	if (!token || !*token)
		return (NULL);
	return (parse_group(token));
}
