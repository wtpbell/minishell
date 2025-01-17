/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_lstclear.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/14 09:11:33 by spyun          #+#    #+#                */
/*   Updated: 2024/10/14 09:11:45 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*curr;
	t_list	*next;

	if (!lst || !del)
		return ;
	curr = *lst;
	while (curr)
	{
		next = curr->next;
		ft_lstdelone(curr, del);
		curr = next;
	}
	*lst = NULL;
}
