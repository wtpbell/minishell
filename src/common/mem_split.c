/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_split.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/06 19:43:42 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/05 23:06:15 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "common.h"
#include "env.h"

static int	count_words(char const *str, char *set)
{
	int	words;
	int	i;

	if (!str)
		return (0);
	words = 0;
	i = 0;
	while (str[i] && ft_strchr(set, str[i]))
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_strchr(set, str[i]))
		{
			words++;
			while (str[i] && !ft_strchr(set, str[i]))
				i++;
		}
		else
			i++;
	}
	return (words);
}

static size_t	mem_strlen(char const *str, char *set)
{
	size_t	len;

	len = 0;
	while (str[len] && !ft_strchr(set, str[len]))
		len++;
	return (len);
}

static int	mem_strcpy(char *dest, char const *src, char *set)
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

void	free_split(char **arr, int i)
{
	while (i > 0)
		free(arr[--i]);
	free(arr);
}

char	**mem_split(char const *str, char *set)
{
	int		words;
	int		i;
	int		j;
	char	**arr;

	words = count_words(str, set);
	arr = (char **)malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (str && str[j] && ft_strchr(set, str[j]))
		j++;
	while (i < words)
	{
		arr[i] = (char *)malloc(sizeof(char) * (mem_strlen(str + j, set) + 1));
		if (!arr[i])
			return (free_split(arr, i), NULL);
		j += mem_strcpy(arr[i], str + j, set);
		i++;
	}
	arr[i] = 0;
	return (arr);
}
