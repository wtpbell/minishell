/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_split.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/06 19:43:42 by bewong        #+#    #+#                 */
/*   Updated: 2025/03/12 19:41:00 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "common.h"
#include "env.h"

static int	is_delimiter(char c, char *set)
{
	if (ft_strchr(set, c) != NULL)
		return (true);
	return (false);
}

static size_t	wordcount(char const *s, char *set)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 && !is_delimiter(s[i], set)) || \
		(is_delimiter(s[i], set) && s[i + 1] != '\0' && \
			!is_delimiter(s[i + 1], set)))
			size++;
		i++;
	}
	return (size);
}

static char	*mem_strndup(const char *s, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)ft_calloc(sizeof(char), (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}

static char	**free_split(char **list)
{
	size_t	i;

	i = 0;
	while (list[i])
		free(list[i++]);
	free(list);
	return (NULL);
}

char	**mem_split(char const *s, char *set)
{
	char	**list;
	size_t	i;
	size_t	j;
	size_t	temp;

	if (!s || !set)
		return (NULL);
	i = 0;
	j = 0;
	list = (char **)ft_calloc(sizeof(char *), wordcount(s, set) + 1);
	if (!list)
		return (NULL);
	while (i < wordcount(s, set) && s[j] != '\0')
	{
		while (is_delimiter(s[j], set))
			j++;
		temp = j;
		while (s[j] != '\0' && !is_delimiter(s[j], set))
			j++;
		list[i] = mem_strndup(&s[temp], j - temp);
		if (!list[i++])
			return (free_split(list));
	}
	return (list);
}
