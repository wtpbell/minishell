/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_expansion_handler.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/30 11:14:56 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/03 14:21:11 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*handle_var_default(char *var_name, char *default_value)
{
	char	*value;

	value = getenv(var_name);
	if (!value || !*value)
		return (ft_strdup(default_value));
	return (ft_strdup(value));
}

static char	*handle_var_assign(char *var_name, char *assign_value)
{
	char	*value;

	value = getenv(var_name);
	if (!value | !*value)
	{
		setenv(var_name, assign_value, 1);
		return (ft_strdup(assign_value));
	}
	return (ft_strdup(value));
}

static char	*handle_var_error(char *var_name, char *error_msg)
{
	char	*value;

	value = getenv(var_name);
	if (!value || !*value)
	{
		ft_putstr_fd(error_msg, STDERR_FILENO);
		return (NULL);
	}
	return (ft_strdup(value));
}

char	*expand_special_param(const char *param)
{
	if (!ft_strcmp(param, "?"))
		return (ft_itoa(g_exit_status));
	if (!ft_strcmp(param, "$"))
		return (ft_itoa(getpid()));
	if (!ft_strcmp(param, "#"))
		return (ft_strdup("0"));
	return (ft_strdup(""));
}

char	*handle_extended_expansion(char *var_name, char *operator, char *word)
{
	if (!operator)
		return (ft_strdup(getenv(var_name)));
	if (!ft_strcmp(operator, ":-"))
		return (handle_var_default(var_name, word));
	if (!ft_strcmp(operator, ":="))
		return (handle_var_assign(var_name, word));
	if (!ft_strcmp(operator, ":?"))
		return (handle_var_error(var_name, word));
	return (ft_strdup(""));
}
