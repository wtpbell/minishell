/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_exit_status.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/12 14:46:42 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/12 15:02:20 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "expander.h"

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
