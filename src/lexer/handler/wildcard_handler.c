/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard_handler.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/30 11:15:13 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/04 20:18:16 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	has_wildcard(const char *str)
{
	if (!str)
		return (0);
	return (ft_strchr(str, '*') != NULL);
}

char	**create_wildcard_token(const char *pattern)
{
	char	**result;

	if (!pattern)
		return (NULL);
	result = (char **)malloc(sizeof(char *) * 2);
	if (!result)
		return (NULL);
	result[0] = ft_strdup(pattern);
	if (!result[0])
	{
		free(result);
		return (NULL);
	}
	result[1] = NULL;
	return (result);
}
