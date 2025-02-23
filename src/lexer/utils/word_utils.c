/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 10:23:45 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/21 09:38:02 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*join_words(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

/* Check if exit status variable */
int	is_exit_status_var(const char *str)
{
	if (str[0] == '$' && str[1] == '?')
		return (1);
	return (0);
}
