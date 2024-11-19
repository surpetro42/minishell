/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:18:35 by ayeganya          #+#    #+#             */
/*   Updated: 2024/01/25 17:18:36 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_compare(const char *haystack, const char *needle)
{
	int	i;

	i = 0;
	while (needle[i])
	{
		if (haystack[i] != needle[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	hstk_size;
	size_t	ndl_size;

	if (!*needle)
		return ((char *)haystack);
	if (len == 0)
		return (0);
	i = 0;
	hstk_size = ft_strlen(haystack);
	ndl_size = ft_strlen(needle);
	if (ndl_size > hstk_size || ndl_size > len)
		return (0);
	while (i <= hstk_size - ndl_size && i <= len - ndl_size)
	{
		if (haystack[i] == needle[0] && ft_compare(&haystack[i], needle))
			return ((char *)&(haystack[i]));
		i++;
	}
	return (0);
}
