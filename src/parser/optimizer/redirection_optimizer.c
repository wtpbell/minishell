/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection_optimizer.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/29 13:15:54 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/01 12:58:47 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Check if the redirection should be removed */
static int	should_remove_redir(t_redir *curr, t_last_redir *last)
{
	return ((curr->type == TOKEN_REDIR_IN && curr != last->in)
		|| (curr->type == TOKEN_REDIR_OUT && curr != last->out)
		|| (curr->type == TOKEN_HEREDOC && curr != last->heredoc)
		|| (curr->type == TOKEN_APPEND && curr != last->append));
}

/* Free the redirection node */
static void	free_redir_node(t_redir *curr)
{
	if (curr->file)
		free(curr->file);
	if (curr->delimiter)
		free(curr->delimiter);
	if (curr->heredoc_file)
		free(curr->heredoc_file);
	free(curr);
}

/* Remove overridden redirections */
static void	remove_overridden_redirs(t_redir **redir, t_last_redir *last)
{
	t_redir	*curr;
	t_redir	*next;
	t_redir	*prev;

	prev = NULL;
	curr = *redir;
	while (curr)
	{
		next = curr->next;
		if (should_remove_redir(curr, last))
		{
			if (prev)
				prev->next = next;
			else
				*redir = next;
			free_redir_node(curr);
		}
		else
			prev = curr;
		curr = next;
	}
}

/* Find the last redirections */
static void	find_last_redirs(t_redir *redir, t_last_redir *last)
{
	t_redir	*curr;

	curr = redir;
	while (curr)
	{
		if (curr->type == TOKEN_REDIR_IN)
			last->in = curr;
		else if (curr->type == TOKEN_REDIR_OUT)
			last->out = curr;
		else if (curr->type == TOKEN_HEREDOC)
			last->heredoc = curr;
		else if (curr->type == TOKEN_APPEND)
			last->append = curr;
		curr = curr->next;
	}
}

t_redir	*merge_redirections(t_redir *redir)
{
	t_last_redir	last;

	if (!redir)
		return (NULL);
	ft_bzero(&last, sizeof(t_last_redir));
	find_last_redirs(redir, &last);
	remove_overridden_redirs(&redir, &last);
	return (redir);
}
