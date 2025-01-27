/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_braced_handler.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/23 08:43:42 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/27 09:00:27 by spyun         ########   odam.nl         */
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
static void free_param_exp(t_param_exp *exp)
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

/*
** Parsing of parameters enclosed in curly braces (${var:-word} format)
** @return: 1 if parsing is successful, 0 if parsing fails.
*/
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

/*
** Apply parsed parameter expansion
** If there is no variable and :- operator, use default value
** If there are no variables and no operators, an empty string is returned.
*/
static char	*apply_param_expansion(t_param_exp *exp)
{
	char	*value;

	value = getenv(exp->var_name);
	if (!value && exp->operator && ft_strcmp(exp->operator, ":-") == 0)
		return (ft_strdup(exp->word));
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

/*
** Main function of brace expansion processing
** Handles parameter expansion in the form ${variable name:-default value}
** @return: extended value or NULL (on error)
*/
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
