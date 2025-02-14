/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 17:22:19 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/14 19:11:12 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "common.h"
#include "env.h"

static void	ft_swap(t_env *a, t_env *b)
{
	t_env	tmp;
	
	// tmp = *a;
	// *a = *b;
	// *b = tmp;
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


/* flags to check for redirection types */
int	get_redir_flags(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (O_RDONLY);
	if (type == TOKEN_REDIR_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	if (type == TOKEN_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	if (type == TOKEN_HEREDOC)
		return (O_RDONLY);
	return (0);
}

int	get_redir_fd(t_token_type type)
{
	if (type == TOKEN_REDIR_IN || type == TOKEN_HEREDOC)
		return (0);
	if (type == TOKEN_REDIR_OUT || type == TOKEN_APPEND)
		return (1);
	return (-1);
}
