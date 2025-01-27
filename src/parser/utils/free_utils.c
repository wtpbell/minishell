/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 09:18:14 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/24 08:50:25 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* free redirect list memory */
static void	free_redirections(t_redirection *redir)
{
	t_redirection	*current;
	t_redirection	*next;

	current = redir;
	while (current)
	{
		next = current->next;
		if (current->file)
			free(current->file);
		free(current);
		current = next;
	}
}

/* Free instruction argument array memory */
static void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

/* Free AST full structure memory */
void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->args)
		free_args(node->args);
	if (node->redirections)
		free_redirections(node->redirections);
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}
