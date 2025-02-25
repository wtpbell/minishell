/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mem_itoa.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bewong <bewong@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/06 19:48:00 by bewong        #+#    #+#                 */
/*   Updated: 2025/02/23 01:01:59 by bewong        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "common.h"
#include "env.h"

static size_t	nb_count(int n)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	itoa_dup(char **nb_str, size_t len, unsigned int nb)
{
	if (nb == 0)
		(*nb_str)[--len] = (nb % 10) + '0';
	while (nb != 0)
	{
		(*nb_str)[--len] = (nb % 10) + '0';
		nb /= 10;
	}
}

char	*mem_itoa(int n)
{
	char			*nb_str;
	int				len;
	int				signe;
	unsigned int	nb;

	len = 0;
	signe = 1;
	nb = n;
	if (n < 0)
	{
		nb = -n;
		len = 1;
		signe = -1;
	}
	len += nb_count(nb);
	nb_str = (char *)mem_alloc(sizeof(char) * (len + 1));
	nb_str[len] = '\0';
	if (signe == -1)
		nb_str[0] = '-';
	itoa_dup(&nb_str, len, nb);
	return (nb_str);
}
