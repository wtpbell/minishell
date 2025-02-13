/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 12:17:41 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/13 17:41:51 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "minishell.h"
#include "parser.h"
#include "expander.h"

char	*expand_double_quote(char *str, int *i)
{
	int		j;
	char	*appended;

	str++;
	(*i)++;
	appended = NULL;
	while (str && !(str[j] == '"'))
	{
		if (str[j] == '$')
			appended = append_vars(appended, str+ j, &j);
		else
			appended = append_regular(appended, str +j, &j, "\"$");
	}
	(*i) += j + 1;
	if (!appended)
		return (mem_strdup(""));
	return (appended);
}

char	*expand_single_quote(char *str, int *i)
{
	int	j;

	str++;
	(*i)++;
	j = 0;
	while (str &&!(str[j] == '\''))
		j++;
	(*i) += j + 1;
	return (mem_strndup(str, j));
}
