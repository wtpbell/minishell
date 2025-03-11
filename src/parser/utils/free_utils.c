/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 09:18:14 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/11 10:31:51 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* free redirect list memory */
void	free_redirections(t_redir *redir)
{
	t_redir	*current;
	t_redir	*next;

	if (!redir)
		return ;
	printf("freeing redirections\n");
	current = redir;
	while (current)
	{
		next = current->next;
		if (current->file)
		{
			printf("freeing %s\n", current->file);
			free(current->file);
			current->file = NULL;
		}
		if (current->delimiter)
		{
			printf("freeing %s\n", current->delimiter);
			free(current->delimiter);
			current->delimiter = NULL;
		}
		if (current->heredoc_file)
		{
			printf("freeing %s\n", current->heredoc_file);
			free(current->heredoc_file);
			current->heredoc_file = NULL;
		}
		printf("freeing whole redir\n");
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
		free(args[i]);
		args[i] = NULL;
		i++;
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
		printf("freeing node->left\n");
		free_ast(node->left);
		node->left = NULL;
	}
	if (node->right)
	{
		printf("freeing node->right\n");
		free_ast(node->right);
		node->right = NULL;
	}
	if (node->args)
	{
		free_args(node->args);
		node->args = NULL;
	}
	if (node->arg_quote_types)
	{
		free(node->arg_quote_types);
		node->arg_quote_types = NULL;
	}
	if (node->redirections)
	{
		free_redirections(node->redirections);
		node->redirections = NULL;
	}
	printf("freeing whole node\n");
	free(node);
}
