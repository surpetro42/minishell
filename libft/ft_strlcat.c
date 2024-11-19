/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 20:55:50 by ayeganya          #+#    #+#             */
/*   Updated: 2024/01/22 20:55:52 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	return_d_size;
	size_t	s_size;

	s_size = ft_strlen(src);
	if (dstsize < 1)
		return (dstsize + s_size);
	i = ft_strlen(dst);
	return_d_size = i;
	j = 0;
	if (i < dstsize)
	{
		while (i + 1 < dstsize && src[j])
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = 0;
		return (return_d_size + s_size);
	}
	return (dstsize + s_size);
}
