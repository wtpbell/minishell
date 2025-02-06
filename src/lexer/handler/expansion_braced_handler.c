/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_braced_handler.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 08:43:42 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/05 09:08:28 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Parameter extension structure initialization */
static void	init_param_exp(t_param_exp *exp)
{
	exp->var_name = NULL;
	exp->operator = NULL;
	exp->word = NULL;
}

/* Free the memory of the parameter extension structure */
static void	free_param_exp(t_param_exp *exp)
{
	if (!exp)
		return ;
	if (exp->var_name)
		free(exp->var_name);
	if (exp->operator)
		free(exp->operator);
	if (exp->word)
		free(exp->word);
}

/* Parsing of parameters enclosed in curly braces (${var:-word} format) */
static int	parse_braced_param(char *str, int *pos, t_param_exp *exp)
{
	int	start;
	int	i;

	start = *pos + 2;
	i = start;
	while (str[i] && str[i] != '}' && str[i] != ':' && str[i] != '-')
		i++;
	exp->var_name = ft_substr(str, start, i - start);
	if (!exp->var_name)
		return (0);
	if (str[i] == ':' && str[i + 1] == '-')
	{
		exp->operator = ft_strdup(":-");
		i += 2;
		start = i;
		while (str[i] && str[i] != '}')
			i++;
		exp->word = ft_substr(str, start, i - start);
	}
	*pos = i;
	return (1);
}

/* Apply parsed parameter expansion */
static char	*apply_param_expansion(t_param_exp *exp)
{
	char	*param_token;
	size_t	len;

	len = ft_strlen(exp->var_name) + 4;
	if (exp->operator)
		len += ft_strlen(exp->operator) + ft_strlen(exp->word);
	param_token = (char *)malloc(len);
	if (!param_token)
		return (NULL);
	ft_strlcpy(param_token, "${", len);
	ft_strlcat(param_token, exp->var_name, len);
	if (exp->operator)
	{
		ft_strlcat(param_token, exp->operator, len);
		ft_strlcat(param_token, exp->word, len);
	}
	ft_strlcat(param_token, "}", len);
	return (param_token);
}

/* Main function of brace expansion processing */
char	*handle_braced_expansion(char *str, int *pos, t_quote_state state)
{
	t_param_exp	exp;
	char		*value;

	(void)state;
	init_param_exp(&exp);
	if (!parse_braced_param(str, pos, &exp))
	{
		free_param_exp(&exp);
		return (NULL);
	}
	value = apply_param_expansion(&exp);
	free_param_exp(&exp);
	return (value);
}
