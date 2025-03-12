/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mixed_wildcard_handler.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 15:45:19 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/12 15:56:56 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	is_mixed_quote_wildcard(const char *str, t_quote_type quote_type)
{
	int	has_quote;
	int	has_wild;
	int	i;

	if (!str)
		return (0);
	has_quote = (quote_type == QUOTE_SINGLE || quote_type == QUOTE_DOUBLE
			|| quote_type == QUOTE_MIXED);
	has_wild = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			has_wild = 1;
		i++;
	}
	return (has_quote && has_wild);
}

static void	update_quote_state(char c, int *in_quote, char *quote_char)
{
	if ((c == '\'' || c == '\"') && (!*in_quote || *quote_char == c))
	{
		*in_quote = !*in_quote;
		if (*in_quote)
			*quote_char = c;
		else
			*quote_char = 0;
	}
}

static void	copy_pattern_chars(const char *arg, char *pattern,
		int *i, int *j)
{
	int		in_quote;
	char	quote_char;

	in_quote = 0;
	quote_char = 0;
	while (arg[*i])
	{
		update_quote_state(arg[*i], &in_quote, &quote_char);
		if ((arg[*i] == '\'' || arg[*i] == '\"')
			&& (!in_quote || in_quote))
		{
			(*i)++;
			continue ;
		}
		pattern[(*j)++] = arg[*i];
		(*i)++;
	}
	pattern[*j] = '\0';
}

static char	*create_expanded_pattern(const char *arg)
{
	char	*pattern;
	int		i;
	int		j;

	if (!arg)
		return (NULL);
	pattern = malloc(ft_strlen(arg) + 1);
	if (!pattern)
		return (NULL);
	i = 0;
	j = 0;
	copy_pattern_chars(arg, pattern, &i, &j);
	return (pattern);
}

void	process_mixed_wildcard(t_ast_node *node, int i)
{
	char	*pattern;
	char	**matches;
	int		match_count;

	pattern = create_expanded_pattern(node->args[i]);
	if (!pattern)
		return ;
	match_count = 0;
	matches = get_matching_files(pattern, &match_count);
	free(pattern);
	if (matches && match_count > 0)
	{
		if (!replace_wildcard_arg(node, i, matches, match_count))
		{
			free_matches(matches, match_count);
			return ;
		}
	}
	else if (matches)
		free(matches);
}
