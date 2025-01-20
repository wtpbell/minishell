/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   whitespace.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:20:52 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/20 15:23:12 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	skip_spaces(char **input)
{
	while (**input && (**input == ' ' || **input == '\t'))
		(*input)++;
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}
