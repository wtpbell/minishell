/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   whitespace.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:20:52 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/20 16:29:15 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	skip_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}
