/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_utils2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/12 10:10:56 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/13 17:54:28 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "minishell.h"
#include "parser.h"
#include "expander.h"

char	*append_vars(char *appended, char *str, int *pos)
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
		return (free_alloc(appended), NULL);
	if (!appended)
		return (var);
	tmp = mem_strjoin(appended, var);
	free_alloc(appended);
	free_alloc(var);
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
		return (free_alloc(appended), NULL);
	(*pos) += i;
	if (!appended)
		return (tmp);
	result = mem_strjoin(appended, tmp);
	free_alloc(appended);
	free_alloc(tmp);
	return (result);
}
char	*get_var_values(char *var, int len)
{
	char	*key;
	char	*value;

	key = mem_substr(var, 0, len);
	if (!key)
		return (NULL);
	value = get_env_value(*get_env_list(), key);
	if (!value)
		return (NULL);
	return (mem_strdup(value));
}

char	*expand_var(char *var, int *pos)
{
	int	len;

	var++;
	(*pos)++;
	len = 0;
	if (*var == '?')
	{
		len++;
		(*pos) += len;
		return (get_var_values(var, len));
	}
	if (!ft_isalpha(*var) && *var != '_')
		return (mem_strdup("$"));
	len++;
	while(var[len] && (ft_isalnum(var[len] || var[len] == '_')))
		len++;
	(*pos) += len;
	return (get_var_values(var, len));
}
