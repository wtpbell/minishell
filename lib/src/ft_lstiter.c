/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_lstiter.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/14 09:17:28 by spyun          #+#    #+#                */
/*   Updated: 2024/10/14 09:17:29 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
