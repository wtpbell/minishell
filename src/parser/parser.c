/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 13:02:50 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/10 09:26:43 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	debug_print_token_chain(t_token *token, const char *prefix)
{
	printf("\033[0;33m%s Token Chain: ", prefix);
	while (token)
	{
		printf("[%d:'%s'] -> ", token->type, token->content);
		token = token->next;
	}
	printf("NULL\n\033[0m");
}

void	debug_print_ast_node(t_ast_node *node, int depth, const char *prefix)
{
	int	i;

	if (!node)
		return ;
	printf("\033[0;36m%s", prefix);
	for (i = 0; i < depth; i++)
		printf("  ");
	printf("Node(%p): type=%d, is_subshell=%d\n",
		(void*)node, node->type, node->is_subshell);
	if (node->args)
	{
		printf("%s", prefix);
		for (i = 0; i < depth; i++)
			printf("  ");
		printf("  Args: ");
		i = 0;
		while (node->args[i])
			printf("'%s' ", node->args[i++]);
		printf("\n");
	}
	printf("\033[0m");

	if (node->left)
		debug_print_ast_node(node->left, depth + 1, prefix);
	if (node->right)
		debug_print_ast_node(node->right, depth + 1, prefix);
}

// /* Parse the tokens */
// t_ast_node	*parse(t_token *tokens)
// {
// 	t_ast_node			*root;
// 	t_syntax_error		syntax_status;
// 	t_cmd_valid_error	cmd_status;

// 	if (!tokens)
// 		return (NULL);
// 	root = parse_complete_bonus(&tokens);
// 	if (!root)
// 		return (NULL);
// 	syntax_status = validate_syntax_tree(root);
// 	if (syntax_status != SYNTAX_OK)
// 	{
// 		ft_putendl_fd(get_syntax_error_msg(syntax_status), STDERR_FILENO);
// 		free_ast(root);
// 		return (NULL);
// 	}
// 	cmd_status = validate_command_syntax(root);
// 	if (cmd_status != VALID_SUCCESS)
// 	{
// 		ft_putendl_fd(get_validation_error_msg(cmd_status), STDERR_FILENO);
// 		free_ast(root);
// 		return (NULL);
// 	}
// 	root = optimize_ast(root);
// 	return (root);
// }

t_ast_node	*parse(t_token *tokens)
{
	t_ast_node			*root;
	t_syntax_error		syntax_status;
	t_cmd_valid_error	cmd_status;
	t_token				*current;

	if (!tokens)
		return (NULL);
	current = tokens;
	debug_print_token_chain(current, "Before parsing:");
	root = parse_complete_bonus(&current);
	if (!root)
	{
		ft_putendl_fd("Parse failed to create AST", STDERR_FILENO);
		return (NULL);
	}
	debug_print_ast_node(root, 0, "After parse_complete_bonus:");
	syntax_status = validate_syntax_tree(root);
	if (syntax_status != SYNTAX_OK)
	{
		ft_putendl_fd(get_syntax_error_msg(syntax_status), STDERR_FILENO);
		debug_print_ast_node(root, 0, "Failed at syntax validation:");
		free_ast(root);
		return (NULL);
	}
	cmd_status = validate_command_syntax(root);
	if (cmd_status != VALID_SUCCESS)
	{
		ft_putendl_fd(get_validation_error_msg(cmd_status), STDERR_FILENO);
		debug_print_ast_node(root, 0, "Failed at command validation:");
		free_ast(root);
		return (NULL);
	}
	root = optimize_ast(root);
	debug_print_ast_node(root, 0, "After optimization:");
	return (root);
}
