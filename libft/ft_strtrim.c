/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 20:59:45 by ayeganya          #+#    #+#             */
/*   Updated: 2024/01/26 20:59:46 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	checker(char ch, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (ch == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		i;
	int		j;

	if (!s1)
		return (0);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && checker(s1[i], set))
		i++;
	if ((size_t)i == ft_strlen(s1))
		i = 0;
	while (j >= 0 && checker(s1[j], set))
		j--;
	ptr = (char *)malloc(j - i + 2);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s1 + i, j - i + 2);
	return (ptr);
}
