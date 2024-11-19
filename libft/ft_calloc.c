/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:24:29 by ayeganya          #+#    #+#             */
/*   Updated: 2024/01/26 15:24:30 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	size_t	res_size;
	void	*result;

	if (size && count > INT_MAX / size)
		return (0);
	res_size = count * size;
	result = malloc(res_size);
	if (result == 0)
		return (0);
	i = 0;
	while (i < res_size)
	{
		*(char *)(result + i) = 0;
		i++;
	}
	return (result);
}
