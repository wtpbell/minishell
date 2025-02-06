/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_subst.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/06 19:46:56 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/06 19:47:20 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "common.h"
#include "env.h"

char	*mem_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	unsigned int	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	i = 0;
	if (start > slen)
		len = 0;
	else if (len > slen || (start + len > slen))
		len = slen - start;
	sub = (char *)mem_alloc((len + 1), GENERAL);
	if (!sub)
		return (NULL);
	while (len && len-- > 0)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
