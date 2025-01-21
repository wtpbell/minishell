/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   char_checks.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:20:50 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/20 15:31:18 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_operator(char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '|' || *str == '<' || *str == '>'
		|| *str == '(' || *str == ')'
		|| (*str == '&' && *(str + 1) == '&')
		|| (*str == '|' && *(str + 1) == '|'))
		return (1);
	return (0);
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>'
		|| c == '(' || c == ')' || c == '&'
		|| c == '\'' || c == '\"' || c == ' '
		|| c == '\t' || c == '\n');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}
