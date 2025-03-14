/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_variables.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/26 14:18:19 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/14 09:35:07 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"

static char	*expand_env_var_in_str(char *var_name, t_env *env_list)
{
	char	*env_value;

	if (ft_strcmp(var_name, "?") == 0)
	{
		env_value = get_env_value(env_list, "?");
		if (!env_value)
			return (ft_strdup("0"));
		return (ft_strdup(env_value));
	}
	env_value = get_env_value(env_list, var_name);
	if (env_value)
		return (ft_strdup(env_value));
	return (ft_strdup(""));
}

static int	is_valid_var_char(char c, int first_char)
{
	if (first_char)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

static char	*extract_var_name(const char *str, int *pos)
{
	int		start;
	int		len;
	char	*var_name;

	start = *pos;
	len = 0;
	if (str[*pos] == '?')
	{
		(*pos)++;
		return (ft_strdup("?"));
	}
	while (str[*pos] && is_valid_var_char(str[*pos], len == 0))
	{
		(*pos)++;
		len++;
	}
	if (len == 0)
		return (NULL);
	var_name = ft_substr(str, start, len);
	return (var_name);
}

char	*process_dollar(const char *str, int *i, t_env *env_list,
			t_quote_type quote_type)
{
	char	*var_name;
	char	*value;
	int		var_pos;

	if (*i > 0 && str[*i - 1] == '\\' && quote_type == QUOTE_DOUBLE)
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	(*i)++;
	if (!str[*i] || str[*i] == ' ' || str[*i] == '\t')
		return (ft_strdup("$"));
	var_pos = *i;
	var_name = extract_var_name(str, i);
	if (!var_name)
		return (ft_strdup("$"));
	if (quote_type == QUOTE_SINGLE)
	{
		free(var_name);
		return (ft_substr(str, *i - 1, *i - var_pos + 1));
	}
	value = expand_env_var_in_str(var_name, env_list);
	free(var_name);
	return (value);
}
