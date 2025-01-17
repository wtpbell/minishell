/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_calloc.c                                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/09 10:25:04 by spyun          #+#    #+#                */
/*   Updated: 2024/10/09 10:25:06 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			total_size;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > ((size_t)-1 / size))
		return (NULL);
	total_size = nmemb * size;
	ptr = (unsigned char *)malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
