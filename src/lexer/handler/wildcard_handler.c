/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard_handler.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/30 11:15:13 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/05 09:12:48 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	has_wildcard(const char *str)
{
	if (!str)
		return (0);
	return (ft_strchr(str, '*') != NULL);
}

t_token	*expand_wildcard_pattern(const char *pattern)
{
	char	**matches;
	t_token	*first;
	t_token	*current;
	int		i;

	matches = expand_wildcards(pattern);
	if (!matches)
		return (create_token(ft_strdup(pattern), TOKEN_WORD));
	first = NULL;
	current = NULL;
	i = 0;
	while (matches[i])
	{
		current = create_token(ft_strdup(matches[i]), TOKEN_WORD);
		if (!current)
		{
			free_tokens(first);
			ft_free_strarr(matches);
			return (NULL);
		}
		if (!first)
			first = current;
		else
			add_token(&first, current);
		i++;
	}
	ft_free_strarr(matches);
	return (first);
}


