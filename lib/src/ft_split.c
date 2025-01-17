/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 11:58:38 by spyun         #+#    #+#                 */
/*   Updated: 2024/11/27 12:02:50 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = NULL;
	if (n == 0)
	{
		str = (char *)malloc(1);
		if (str)
			str[0] = '\0';
		return (str);
	}
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (str == 0)
		return (NULL);
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**ft_freeall(char **list)
{
	size_t	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
	return (NULL);
}

static size_t	ft_wordcount(char const *s, char c)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 && s[i] != c) || \
		(s[i] == c && s[i + 1] != '\0' && s[i + 1] != c))
			size++;
		i++;
	}
	return (size);
}

char	**ft_split(char const *s, char c)
{
	char	**list;
	size_t	i;
	size_t	j;
	size_t	temp;

	if (!s)
		return (NULL);
	i = 0;
	j = 0;
	list = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!list)
		return (NULL);
	while (i < ft_wordcount(s, c) && s[j] != '\0')
	{
		while (s[j] == c)
			j++;
		temp = j;
		while (s[j] != c && s[j] != '\0')
			j++;
		list[i] = ft_strndup(&s[temp], j - temp);
		if (list[i++] == 0)
			return (ft_freeall(list));
	}
	list[i] = NULL;
	return (list);
}
