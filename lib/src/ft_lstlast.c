/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_lstlast.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/09 17:20:13 by spyun          #+#    #+#                */
/*   Updated: 2024/10/09 17:20:14 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
