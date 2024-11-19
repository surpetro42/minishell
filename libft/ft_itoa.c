/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:16:12 by ayeganya          #+#    #+#             */
/*   Updated: 2024/01/28 15:16:13 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_worker(char *str, long n, int size)
{
	int	i;

	i = size - 2;
	str[size - 1] = 0;
	while (i >= 0)
	{
		str[i] = n % 10 + '0';
		i--;
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	int		i;
	int		sign;
	char	*result;
	long	temp;

	i = 0;
	sign = 0;
	temp = n;
	if (n < 0 && ++sign)
		temp = (long)n * (-1);
	while ((n >= 10 || n <= -10) && ++i)
		n /= 10;
	result = (char *)malloc(sign + i + 2);
	if (!result)
		return (0);
	if (sign)
	{
		result[0] = '-';
		ft_worker(&result[1], temp, i + 2);
	}
	else
		ft_worker(result, temp, i + 2);
	return (result);
}
