/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_lstdelone.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: spyun <marvin@42.fr>                          +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/10/14 09:08:05 by spyun          #+#    #+#                */
/*   Updated: 2024/10/14 09:08:06 by spyun          ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
}
