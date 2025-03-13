/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wildcard_expander_utils.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/13 16:36:22 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/14 00:01:31 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"
#include "common.h"

char	*join_matches_with_spaces(char **matches, int match_count)
{
	char	*result;
	char	*temp;
	int		i;

	result = NULL;
	i = 0;
	if (!matches || match_count <= 0)
		return (ft_strdup(""));
	result = ft_strdup(matches[0]);
	if (!result)
		return (NULL);
	while (++i < match_count)
	{
		temp = result;
		result = ft_strjoin(result, " ");
		free(temp);
		if (!result)
			return (NULL);
		temp = result;
		result = ft_strjoin(result, matches[i]);
		free(temp);
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*process_wildcard_in_variable(char *value)
{
	char	**matches;
	int		match_count;
	char	*result;

	match_count = 0;
	if (!value || !has_wildcard(value))
		return (value);
	matches = get_matching_files(value, &match_count);
	free(value);
	if (!matches || match_count == 0)
		return (ft_strdup("*"));
	result = join_matches_with_spaces(matches, match_count);
	free_matches(matches, match_count);
	return (result);
}
