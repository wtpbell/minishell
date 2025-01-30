/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection_optimizer.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/29 13:15:54 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/29 16:56:09 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	should_remove_redir(t_redirection *curr, t_last_redirs *last)
{
	return ((curr->type == TOKEN_REDIR_IN && curr != last->in)
		|| (curr->type == TOKEN_REDIR_OUT && curr != last->out)
		|| (curr->type == TOKEN_HEREDOC && curr != last->heredoc)
		|| (curr->type == TOKEN_APPEND && curr != last->append));
}

static void	free_redir_node(t_redirection *curr)
{
	if (curr->file)
		free(curr->file);
	free(curr);
}

static void	remove_overridden_redirs(t_redirection **redir, t_last_redirs *last)
{
	t_redirection	*curr;
	t_redirection	*next;
	t_redirection	*prev;

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

static void	find_last_redirs(t_redirection *redir, t_last_redirs *last)
{
	t_redirection	*curr;

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

t_redirection	*merge_redirections(t_redirection *redir)
{
	t_last_redirs	last;

	if (!redir)
		return (NULL);
	ft_bzero(&last, sizeof(t_last_redirs));
	find_last_redirs(redir, &last);
	remove_overridden_redirs(&redir, &last);
	return (redir);
}
