/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:40:42 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/20 14:30:14 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status = 0;

static int	get_env_len(char *str)
{
	int	len;

	len = 0;
	if (str[len] == '?')
		return (1);
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}

static char	*get_env_value(char *var_name, int len)
{
	char	*name;
	char	*value;

	if (len == 1 && var_name[0] == '?')
		return (ft_itoa(g_exit_status));
	name = ft_substr(var_name, 0, len);
	if (!name)
		return (NULL);
	value = getenv(name);
	free(name);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

char	*expand_env_vars(char *str)
{
	char	*result;
	int		i;
	int		in_quote;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	in_quote = 0;
	while(str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			in_quote = !in_quote;
		if (str[i] == '$' && !in_quote)
		{
			i++;
			if (str[i])
			{
				int len = get_env_len(&str[i]);
				char *value = get_env_value(&str[i], len);
				if (!value)
				{
					free(result);
					return (NULL);
				}
				result = ft_strjoin(result, value);
				free(value);
				i += len - 1;
			}
		}
		result = ft_strjoin(result, &str[i]);
	}
	return (result);
}

void expand_tokens(t_token *tokens)
{
	t_token	*current;
	char	*expanded;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			expanded = expand_env_vars(current->content);
			if (expanded)
			{
				free(current->content);
				current->content = expanded;
			}
		}
		current = current->next;
	}
}
