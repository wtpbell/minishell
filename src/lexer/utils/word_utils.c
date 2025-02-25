/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <spyun@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/18 10:23:45 by spyun         #+#    #+#                 */
/*   Updated: 2025/02/25 14:28:08 by spyun         ########   odam.nl         */
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
