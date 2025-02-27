/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard_handler.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/30 11:15:13 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/27 15:27:01 by spyun         ########   odam.nl         */
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

/* Match pattern with wildcard */
int	match_pattern(const char *pattern, const char *string)
{
	int		i;
	int		j;
	int		star_idx;
	int		string_star_idx;

	i = 0;
	j = 0;
	star_idx = -1;
	string_star_idx = -1;
	while (string[j])
	{
		if (pattern[i] && (pattern[i] == string[j] || pattern[i] == '?'))
		{
			i++;
			j++;
		}
		else if (pattern[i] == '*')
		{
			star_idx = i;
			string_star_idx = j;
			i++;
		}
		else if (star_idx != -1)
		{
			i = star_idx + 1;
			string_star_idx++;
			j = string_star_idx;
		}
		else
			return (0);
	}
	while (pattern[i] == '*')
		i++;
	return (pattern[i] == '\0');
}

