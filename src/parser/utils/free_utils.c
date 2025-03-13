/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 09:18:14 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/13 09:38:37 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_redirections(t_redir *redir)
{
	t_redir	*current;
	t_redir	*next;

	if (!redir)
		return ;
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

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->left)
		free_ast(node->left);
	if (node->right)
		free_ast(node->right);
	if (node->args)
		free_args(node->args);
	if (node->arg_quote_types)
		free(node->arg_quote_types);
	if (node->redirections)
		free_redirections(node->redirections);
	free(node);
}
