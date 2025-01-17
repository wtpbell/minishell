/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: spyun <marvin@42.fr>                         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 12:03:18 by spyun         #+#    #+#                 */
/*   Updated: 2025/01/06 10:09:27 by spyun         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	get_num_len(int n)
{
	size_t	len;
	long	num;

	num = n;
	len = 1;
	if (num < 0)
	{
		len++;
		num = -num;
	}
	while (num >= 10)
	{
		len++;
		num /= 10;
	}
	return (len);
}

static void	write_number(char *result, long num, int len, int sign)
{
	result[len] = '\0';
	if (sign)
		result[0] = '-';
	if (num == 0)
		result[0] = '0';
	while (num > 0)
	{
		result[--len] = num % 10 + '0';
		num /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	long	num;
	int		len;
	int		sign;

	num = n;
	sign = 0;
	if (num < 0)
	{
		sign = 1;
		num = -num;
	}
	len = get_num_len(n);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	write_number(result, num, len, sign);
	return (result);
}
