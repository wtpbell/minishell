/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_handler.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/26 13:34:12 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/26 13:35:02 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"


static char	*expand_env_var_in_str(char *var_name, t_env *env_list)
{
	char	*env_value;

	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(g_exit_status));
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

static char	*process_dollar(const char *str, int *i, t_env *env_list,
							t_quote_type quote_type)
{
	char	*var_name;
	char	*value;
	int		var_pos;

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

char	*handle_expansion(t_tokenizer *tokenizer, const char *arg)
{
	int			i;
	char		*result;
	char		*tmp;
	char		*tmp2;
	char		*expanded;
	t_quote_type	current_quote;
	t_env		*env_list;

	(void)*tokenizer;
	env_list = *get_env_list();
	if (!arg)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	current_quote = QUOTE_NONE;
	while (arg[i])
	{
		if (arg[i] == '\'' && current_quote != QUOTE_DOUBLE)
			current_quote = (current_quote == QUOTE_SINGLE) ? QUOTE_NONE : QUOTE_SINGLE;
		else if (arg[i] == '\"' && current_quote != QUOTE_SINGLE)
			current_quote = (current_quote == QUOTE_DOUBLE) ? QUOTE_NONE : QUOTE_DOUBLE;
		else if (arg[i] == '$' && current_quote != QUOTE_SINGLE)
		{
			tmp = ft_substr(arg, 0, i);
			tmp2 = ft_strjoin(result, tmp);
			free(tmp);
			free(result);
			result = tmp2;
			expanded = process_dollar(arg, &i, env_list, current_quote);
			tmp = ft_strjoin(result, expanded);
			free(expanded);
			free(result);
			result = tmp;
			continue ;
		}
		tmp = ft_substr(arg, i, 1);
		tmp2 = ft_strjoin(result, tmp);
		free(tmp);
		free(result);
		result = tmp2;
		i++;
	}
	return (result);
}
