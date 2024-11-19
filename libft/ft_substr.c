/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:12:46 by ayeganya          #+#    #+#             */
/*   Updated: 2024/11/07 01:07:28 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;

	if (s == 0)
		return (0);
	if (start > ft_strlen(s))
	{
		result = (char *)malloc(1);
		if (!result)
			return (0);
		*result = 0;
		return (result);
	}
	if (ft_strlen(s) - start < len)
		result = (char *)malloc(ft_strlen(s) - start + 1);
	else
		result = (char *)malloc(len + 1);
	if (!result)
		return (0);
	ft_strlcpy(result, s + start, len +1);
	return (result);
}
