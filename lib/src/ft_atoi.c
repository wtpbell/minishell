/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/08 10:34:01 by spyun         #+#    #+#                 */
/*   Updated: 2024/12/02 15:49:27 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static size_t	skip_whitespace(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	return (i);
}

static int	check_overflow(long result, int sign, char c)
{
	if ((result > LONG_MAX / 10)
		|| (result == LONG_MAX / 10 && (c - '0') > LONG_MAX % 10))
	{
		if (sign == 1)
			return (-1);
		else
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	long	result;
	int		sign;
	int		overflow_check;

	i = skip_whitespace(str);
	result = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		overflow_check = check_overflow(result, sign, str[i]);
		if (overflow_check != 1)
			return (overflow_check);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}
