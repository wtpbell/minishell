/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/13 14:08:24 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/13 17:12:23 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include "common.h"

static char	*ft_strndup(const char *s, size_t n)
{
	char			*res;
	unsigned int	i;

	i = 0;
	res = ft_calloc(sizeof(char), (n + 1));
	if (res == NULL)
		return (NULL);
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	return (res);
}

static char	**create_env_pair(const char *key, const char *value)
{
	char	**result;

	result = (char **)ft_calloc(sizeof(char *), 3);
	if (!result)
		return (NULL);
	result[0] = ft_strdup(key);
	if (!result[0])
	{
		free(result);
		return (NULL);
	}
	if (value)
	{
		result[1] = ft_strdup(value);
		if (!result[1])
		{
			free(result[0]);
			free(result);
			return (NULL);
		}
	}
	else
		result[1] = NULL;
	result[2] = NULL;
	return (result);
}

char	**split_env_var(const char *env_str)
{
	char	*pos;
	char	**result;
	char	*key;

	if (!env_str)
		return (NULL);
	pos = ft_strchr(env_str, '=');
	if (pos)
	{
		key = ft_strndup(env_str, pos - env_str);
		if (!key)
			return (NULL);
		result = create_env_pair(key, pos + 1);
		free(key);
		return (result);
	}
	else
		return (create_env_pair(env_str, NULL));
}
