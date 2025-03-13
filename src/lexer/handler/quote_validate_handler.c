/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_validate_handler.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/22 10:01:10 by spyun         #+#    #+#                 */
/*   Updated: 2025/03/13 13:41:51 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

static int	process_quote(const char *input, int *i)
{
	char	current_quote;
	int		closing_pos;

	current_quote = input[*i];
	closing_pos = find_closing_quote(input, *i, current_quote);
	if (closing_pos == -1)
	{
		ft_putstr_fd(RED, STDERR_FILENO);
		ft_putendl_fd("minishell: unclosed quote detected", STDERR_FILENO);
		ft_putstr_fd(RESET, STDERR_FILENO);
		return (0);
	}
	*i = closing_pos;
	return (1);
}

int	validate_quotes(const char *input)
{
	int	i;

	if (!input || !*input)
		return (1);
	i = 0;
	while (input[i])
	{
		if (input[i] == '\\' && input[i + 1])
		{
			i = i + 2;
			continue ;
		}
		if ((input[i] == '\'' || input[i] == '\"') && !is_escaped(input, i))
			if (!process_quote(input, &i))
				return (0);
		i++;
	}
	return (1);
}
