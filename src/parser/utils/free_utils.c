/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 09:18:14 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/11 08:34:32 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* free redirect list memory */
void	free_redirections(t_redir *redir)
{
	t_redir	*current;
	t_redir	*next;

	current = redir;
	while (current)
	{
		next = current->next;
		if (current->file)
			free(current->file);
		if (current->delimiter)
			free(current->delimiter);
		if (current->heredoc_file)
			free(current->heredoc_file);
		free(current);
		current = next;
	}
}

/* Free instruction argument array memory */
// void	free_args(char **args)
// {
// 	int	i;

// 	if (!args)
// 		return ;
// 	i = 0;
// 	while (args[i])
// 	{
// 		printf("freeing %s\n", args[i]);
// 		free(args[i++]);
// 	}
// 	free(args);
// }

void free_args(char **args)
{
	int i;

	if (!args)
		return;

	printf("Freeing args array at %p\n", (void*)args);
	i = 0;
	while (args[i])
	{
		printf("Freeing arg[%d] at %p: '%s'\n", i, (void*)args[i], args[i]);
		free(args[i++]);
	}
	free(args);
	printf("Args array freed\n");
}

/* Free AST full structure memory */
void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->left)
	{
		printf("am i freeing node->left\n");
		free_ast(node->left);
	}
	if (node->right)
	{
		printf("am i freeing node->right\n");
		free_ast(node->right);
	}
	printf("Freeing node args at %p\n", (void*)node->args);
	if (node->args)
		free_args(node->args);
	if (node->arg_quote_types)
		free(node->arg_quote_types);
	if (node->redirections)
		free_redirections(node->redirections);
	printf("am i freeing whole node\n");
	free(node);
}
