/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 10:10:56 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/12 12:36:07 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "minishell.h"
#include "parser.h"
#include "expander.h"

static char	*append_vars(char *appended, char *str, int *pos)
{
	char	*var;
	char	*tmp;
	int		i;

	i = 0;
	var = NULL;
	if (*str == '"')
		var = expand_double_quote(str, &i);
	else if (*str == '\'')
		var = expand_single_quote(str, &i);
	else
		var = expand_var(str, &i);
	(*pos) += i;
	if (!var)
		return (free_alloc(appended, GENERAL), NULL);
	if (!appended)
		return (var);
	tmp = mem_strjoin(appended, var);
	free_alloc(appended, GENERAL);
	free_alloc(var, GENERAL);
	return (tmp);
}

char	*append_regular(char *appended, char *str, int *pos, char *set)
{
	char	*tmp;
	char	*result;
	int		i;

	i = 0;
	while (str[i] && !ft_strchr(set, str[i]))
		i++;
	tmp = NULL;
	if (i > 0)
		tmp = mem_strndup(str, i);
	if (!tmp)
		return (free_alloc(appended, GENERAL), NULL);
	(*pos) += i;
	if (!appended)
		return (tmp);
	result = mem_strjoin(appended, tmp);
	free_alloc(appended, GENERAL);
	free_alloc(tmp, GENERAL);
	return (result);
}
