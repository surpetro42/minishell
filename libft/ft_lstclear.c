/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:09:11 by ayeganya          #+#    #+#             */
/*   Updated: 2024/01/30 15:09:12 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;

	if (!lst || !*lst || !del)
		return ;
	ptr = (*lst)->next;
	while (ptr)
	{
		ft_lstdelone(*lst, del);
		*lst = ptr;
		ptr = (*lst)->next;
	}
	ft_lstdelone(*lst, del);
	*lst = 0;
}
