/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_lstsize.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/09 17:11:13 by spyun          #+#    #+#                */
/*   Updated: 2024/10/09 17:11:15 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
