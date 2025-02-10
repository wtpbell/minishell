/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_strndup.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/06 19:46:01 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/06 19:53:06 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "common.h"
#include "env.h"


char	*men_strndup(const char *str, int n)
{
	char	*new_str;
	int		min;

	min = ft_strlen(str);
	if (n < min)
		min = n;
	new_str = (char *)mem_alloc((min + 1), GENERAL);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, str, min);
	new_str[min] = '\0';
	return (new_str);
}
