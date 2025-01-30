/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_validator.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/22 10:01:10 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/24 09:02:53 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* Check if the character is escaped */
static int	is_escaped(const char *str, int pos)
{
	int	count;

	count = 0;
	while (pos > 0 && str[pos - 1] == '\\')
	{
		count++;
		pos--;
	}
	return (count % 2);
}

/* Check if there are unclosed quotations */
static int	find_closing_quote(const char *str, int start, char quote_char)
{
	int	i;

	i = start + 1;
	while (str[i])
	{
		if (str[i] == quote_char && !is_escaped(str, i))
			return (i);
		i++;
	}
	return (-1);
}

/* Validate quotes in input string */
int	validate_quotes(const char *input)
{
	int		i;
	char	current_quote;
	int		closing_pos;

	i = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && !is_escaped(input, i))
		{
			current_quote = input[i];
			closing_pos = find_closing_quote(input, i, current_quote);
			if (closing_pos == -1)
			{
				ft_putstr_fd("minishell: unclosed quote detected\n",
					STDERR_FILENO);
				return (0);
			}
			i = closing_pos;
		}
		i++;
	}
	return (1);
}

/* Set rules for handling special characters inside quotes */
int	should_expand_in_quotes(char c, char quote_type)
{
	if (quote_type == '\'')
		return (0);
	if (quote_type == '\"')
	{
		if (c == '$' || c == '`' || c == '\\')
			return (1);
	}
	return (0);
}
