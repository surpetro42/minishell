/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:21:08 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/09 00:55:15 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*subf(const char *s)
{
	char	*ptr;

	ptr = (char *)malloc(ft_strlen(s) + 1);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s, ft_strlen(s) + 1);
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	s1_size;
	size_t	s2_size;

	if (s1 == 0 && s2 == 0)
		return (0);
	else if (s1 == 0)
		return (subf(s2));
	else if (s2 == 0)
		return (subf(s1));
	else
	{
		s1_size = ft_strlen(s1);
		s2_size = ft_strlen(s2);
		ptr = (char *)malloc(s1_size + s2_size + 1);
		if (!ptr)
			return (0);
		ft_strlcpy(ptr, s1, s1_size + 1);
		ft_strlcat(ptr, s2, s1_size + s2_size + 1);
		return (ptr);
	}
}
