/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_exit_status.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 14:46:42 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/13 11:10:16 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"

void	handle_exit_status_expansion(t_ast_node *node, int i)
{
	char	*status;
	char	*result;

	status = ft_strdup(get_env_value(*get_env_list(), "?"));
	if (!status)
		status = ft_strdup("0");
	if (node->args[i][2] != '\0')
	{
		result = ft_strjoin(status, node->args[i] + 2);
		free(status);
		free(node->args[i]);
		node->args[i] = result;
	}
	else
	{
		free(node->args[i]);
		node->args[i] = status;
	}
}

char	*extract_var_name_expander(char *arg, int *var_len)
{
	char	*var_name;
	int		len;

	len = 0;
	while (arg[len] && (ft_isalnum(arg[len]) || arg[len] == '_'))
		len++;
	var_name = ft_substr(arg, 0, len);
	*var_len = len;
	return (var_name);
}

char	*handle_exit_status(int *i, char *result)
{
	char	*tmp;
	char	*exit_status;
	t_env	*env_list;

	env_list = *get_env_list();
	exit_status = ft_strdup(get_env_value(env_list, "?"));
	if (!exit_status)
		exit_status = ft_strdup("0");
	tmp = ft_strjoin(result, exit_status);
	free(exit_status);
	free(result);
	*i += 2;
	return (tmp);
}

char	*process_exit_status_in_dquotes(const char *arg, int *i,
			char *result)
{
	char	*tmp;
	char	*exit_status;
	t_env	*env_list;

	result = process_string_char(arg[*i], result);
	if (!result)
		return (NULL);
	(*i)++;
	env_list = *get_env_list();
	exit_status = ft_strdup(get_env_value(env_list, "?"));
	if (!exit_status)
		exit_status = ft_strdup("0");
	tmp = ft_strjoin(result, exit_status);
	free(exit_status);
	free(result);
	result = tmp;
	if (!result)
		return (NULL);
	*i += 2;
	result = process_string_char(arg[*i], result);
	if (!result)
		return (NULL);
	(*i)++;
	return (result);
}
