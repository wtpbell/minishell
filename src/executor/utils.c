/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 17:22:19 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/02 21:21:09 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "common.h"
#include "env.h"

static void	ft_swap(t_env *a, t_env *b)
{
	t_env	tmp;

	tmp.key = a->key;
	tmp.value = a->value;
	tmp.scope = a->scope;
	tmp.hide = a->hide;
	a->key = b->key;
	a->value = b->value;
	a->scope = b->scope;
	a->hide = b->hide;
	b->key = tmp.key;
	b->value = tmp.value;
	b->scope = tmp.scope;
	b->hide = tmp.hide;
}

void	sort_env(t_env **envs)
{
	t_env	*env;
	bool	did_swap;

	if (!envs || !*envs || !(*envs)->next)
		return ;
	while (true)
	{
		env = *envs;
		did_swap = 0;
		while (env->next)
		{
			if (ft_strcmp(env->key, env->next->key) > 0)
			{
				ft_swap(env, env->next);
				did_swap = 1;
			}
			env = env->next;
		}
		if (!did_swap)
			break ;
	}
}

void	cleanup_heredocs(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC && redir->heredoc_file)
			unlink(redir->heredoc_file);
		redir = redir->next;
	}
}

size_t	count_pipes(t_ast_node *node)
{
	size_t	count;

	count = 0;
	while (node)
	{
		if (node->type == TOKEN_PIPE)
			count++;
		node = node->right;
	}
	return (count);
}
