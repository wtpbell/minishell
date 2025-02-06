/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/28 17:22:19 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/06 09:30:48 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
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

static int	ft_count_words(char const *s, char *set)
{
	int	words;
	int	i;

	if (!s)
		return (0);
	words = 0;
	i = 0;
	while (s[i] && ft_strchr(set, s[i]))
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_strchr(set, s[i]))
		{
			words++;
			while (s[i] && !ft_strchr(set, s[i]))
				i++;
		}
		else
			i++;
	}
	return (words);
}

static size_t	ft_strlen_c(char const *s, char *set)
{
	size_t	len;

	len = 0;
	while (s[len] && !ft_strchr(set, s[len]))
		len++;
	return (len);
}

static int	ft_strcpy_k(char *dest, char const *src, char *set)
{
	int	i;

	i = 0;
	while (src[i] && !ft_strchr(set, src[i]))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	while (src[i] && ft_strchr(set, src[i]))
		i++;
	return (i);
}

char	**ft_split_mini(char const *s, char *set)
{
	int		words;
	int		i;
	int		k;
	char	**arr;

	words = ft_count_words(s, set);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	i = 0;
	k = 0;
	while (s && s[k] && ft_strchr(set, s[k]))
		k++;
	while (i < words)
	{
		arr[i] = (char *)malloc(sizeof(char) * (ft_strlen_c(s + k, set) + 1));
		k += ft_strcpy_k(arr[i], s + k, set);
		i++;
	}
	arr[i] = 0;
	return (arr);
}
