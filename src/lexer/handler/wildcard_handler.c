/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard_handler.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/30 11:15:13 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/10 17:26:02 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Check if the string contains a wildcard */
int	has_wildcard(const char *str)
{
	if (!str)
		return (0);
	return (ft_strchr(str, '*') != NULL);
}

/* Create a wildcard token */
t_token	*handle_wildcard_token(const char *str)
{
	return (create_token(ft_strdup(str), TOKEN_WILDCARD));
}
