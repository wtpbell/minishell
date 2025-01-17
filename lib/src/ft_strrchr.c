/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_strrchr.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/08 09:57:15 by spyun          #+#    #+#                */
/*   Updated: 2024/10/08 09:57:17 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	if ((unsigned char)c == '\0')
		return ((char *)s + i);
	while (i > 0)
	{
		if (s[i - 1] == (char)c)
			return ((char *)s + (i - 1));
		i--;
	}
	return (NULL);
}
