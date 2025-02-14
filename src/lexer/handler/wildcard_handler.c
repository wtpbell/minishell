/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard_handler.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/30 11:15:13 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/14 11:00:15 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Check if the string contains a wildcard */
int	has_wildcard(const char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '*')
			return (1);
		str++;
	}
	return (0);
}

/* Create a wildcard token with TOKEN_WILDCARD type */
t_token	*handle_wildcard_token(const char *str)
{
	t_token_type	type;

	if (!str)
		return (NULL);
	type = TOKEN_WILDCARD;
	return (create_token(ft_strdup(str), type));
}

/* Match one character with pattern */
static int	match_one(char pattern, char string)
{
	if (pattern == '?')
		return (1);
	return (pattern == string);
}

/* Match pattern with wildcard */
int	match_pattern(const char *pattern, const char *string)
{
	if (!pattern || !string)
		return (0);
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (!*pattern)
			return (1);
		while (*string)
		{
			if (match_pattern(pattern, string))
				return (1);
			string++;
		}
		return (0);
	}
	if (!*string)
		return (0);
	if (match_one(*pattern, *string))
		return (match_pattern(pattern + 1, string + 1));
	return (0);
}
