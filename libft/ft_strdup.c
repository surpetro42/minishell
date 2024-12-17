/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:41:35 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/09 00:05:14 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	ssize;

	ssize = ft_strlen(s1);
	ptr = (char *)malloc(ssize + 1);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s1, ssize + 1);
	return (ptr);
}
