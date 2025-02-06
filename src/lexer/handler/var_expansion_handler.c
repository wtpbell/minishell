/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   var_expansion_handler.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/30 11:14:56 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/05 09:10:14 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Handles variable default expansion */
static char	*handle_var_default(char *var_name, char *default_value)
{
	char	*expansion_token;
	size_t	total_len;

	total_len = 4;
	total_len += ft_strlen(var_name);
	total_len += ft_strlen(default_value);
	expansion_token = (char *)malloc(total_len + 1);
	if (!expansion_token)
		return (NULL);
	ft_strlcpy(expansion_token, "${", total_len + 1);
	ft_strlcat(expansion_token, var_name, total_len + 1);
	ft_strlcat(expansion_token, ":-", total_len + 1);
	ft_strlcat(expansion_token, default_value, total_len + 1);
	ft_strlcat(expansion_token, "}", total_len + 1);
	return (expansion_token);
}

/* Handles variable assignment expansion */
static char	*handle_var_assign(char *var_name, char *assign_value)
{
	char	*var_token;
	int		len;

	len = ft_strlen(var_name) + ft_strlen(assign_value) + 4;
	var_token = (char *)malloc(len);
	if (!var_token)
		return (NULL);
	ft_strlcpy(var_token, "${", len);
	ft_strlcat(var_token, var_name, len);
	ft_strlcat(var_token, ":=", len);
	ft_strlcat(var_token, assign_value, len);
	ft_strlcat(var_token, "}", len);
	return (var_token);
}

/* Handles variable error expansion */
static char	*handle_var_error(char *var_name, char *error_msg)
{
	char	*var_token;
	int		len;

	len = ft_strlen(var_name) + ft_strlen(error_msg) + 4;
	var_token = (char *)malloc(len);
	if (!var_token)
		return (NULL);
	ft_strlcpy(var_token, "${", len);
	ft_strlcat(var_token, var_name, len);
	ft_strlcat(var_token, ":?", len);
	ft_strlcat(var_token, error_msg, len);
	ft_strlcat(var_token, "}", len);
	return (var_token);
}

/* Expands special parameters */
char	*expand_special_param(const char *param)
{
	char	*special_token;

	special_token = (char *)malloc(3);
	if (!special_token)
		return (NULL);
	special_token[0] = '$';
	special_token[1] = *param;
	special_token[2] = '\0';
	return (special_token);
}

/* Handles extended expansion */
char	*handle_extended_expansion(char *var_name, char *operator, char *word)
{
	if (!operator)
		return (ft_strjoin("$", var_name));
	if (!ft_strcmp(operator, ":-"))
		return (handle_var_default(var_name, word));
	if (!ft_strcmp(operator, ":="))
		return (handle_var_assign(var_name, word));
	if (!ft_strcmp(operator, ":?"))
		return (handle_var_error(var_name, word));
	return (ft_strdup(""));
}
