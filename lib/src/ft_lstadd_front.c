/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_lstadd_front.c                                   :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/09 16:55:11 by spyun          #+#    #+#                */
/*   Updated: 2024/10/09 16:55:12 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
