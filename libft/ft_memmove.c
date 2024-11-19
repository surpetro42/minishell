/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:17:22 by ayeganya          #+#    #+#             */
/*   Updated: 2024/01/22 19:09:06 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*from;
	char	*to;

	from = (char *)src;
	to = (char *)dst;
	if (from < to && len)
	{
		i = len - 1;
		while (i + 1 >= 1)
		{
			to[i] = from[i];
			i--;
		}
		return (dst);
	}
	else if (to < from && len)
	{
		i = 0;
		while (i < len && ++i)
			to[i - 1] = from[i - 1];
		return (dst);
	}
	else
		return (dst);
}
