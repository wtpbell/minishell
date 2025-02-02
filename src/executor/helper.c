/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helper.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/30 22:36:21 by bewong        #+#    #+#                 */
/*   Updated: 2025/01/31 00:13:30 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "env.h"
#include <sys/stat.h>

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

int	check_paths(char *full_path)
{
	char	**paths;
	int		i;
	// char	*joined;
	// int		status_;

	if (full_path[0] == '/' && full_path[1] == '\0')
		return (0);
	paths = ft_split_mini(full_path, "/");
	i = 0;
	while (paths[i] != NULL)
		printf("%s: ", paths[i]);
	// joined = NULL;
	// status_ = check_leading_paths(full_path, paths, &joined, &i);
	// if (status_ != 0)
	// 	return (status_);
	// return (check_last_path(full_path, paths, &joined, i));
	return (1);
}
