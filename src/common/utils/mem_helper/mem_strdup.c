/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_strdup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/06 20:01:19 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/06 20:06:05 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "common.h"
#include "env.h"

char	*mem_strdup(const char *str)
{
	char	*nstr;

	nstr = (char *)mem_alloc((ft_strlen(str) + 1), GENERAL);
	if (!nstr)
		return (NULL);
	ft_memcpy(nstr, str, (ft_strlen(str) + 1));
	return (nstr);
}
