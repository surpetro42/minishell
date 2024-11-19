/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:43:26 by ayeganya          #+#    #+#             */
/*   Updated: 2024/01/31 16:43:27 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*temp;

	if (!lst || !f || !del)
		return (0);
	result = ft_lstnew(f(lst->content));
	if (!result)
		ft_lstclear(&result, del);
	while (lst->next)
	{
		lst = lst->next;
		temp = ft_lstnew(f(lst->content));
		if (!result)
			ft_lstclear(&result, del);
		ft_lstadd_back(&result, temp);
	}
	return (result);
}
