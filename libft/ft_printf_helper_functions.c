/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:21:40 by ayeganya          #+#    #+#             */
/*   Updated: 2024/02/12 12:21:41 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_uitoa(unsigned int n)
{
	int		i;
	char	*result;
	long	temp;

	i = 0;
	temp = n;
	while (n >= 10 && ++i)
		n /= 10;
	result = (char *)malloc(i + 2);
	if (!result)
		return (0);
	result[i + 1] = 0;
	while (i >= 0)
	{
		result[i] = temp % 10 + '0';
		i--;
		temp /= 10;
	}
	return (result);
}

void	ft_xitoa_worker(char *str, unsigned long n, int size, char cap)
{
	char			x_sign[6];
	int				i;
	unsigned long	temp;

	i = 0;
	if (cap == 'X')
		while (i < 6 && ++i)
			x_sign[i - 1] = 'A' + i - 1;
	else
		while (i < 6 && ++i)
			x_sign[i - 1] = 'a' + i - 1;
	str[size - 1] = 0;
	while (size - 2 >= 0)
	{
		temp = n % 16;
		if (temp < 10)
			str[size - 2] = temp + '0';
		else
			str[size - 2] = x_sign[temp - 10];
		size--;
		n /= 16;
	}
}

char	*ft_xitoa(unsigned long n, char cap)
{
	int				i;
	char			*result;
	unsigned long	temp;

	i = 0;
	temp = n;
	while (n >= 16 && ++i)
		n /= 16;
	result = (char *)malloc(i + 2);
	if (!result)
		return (0);
	ft_xitoa_worker(result, temp, i + 2, cap);
	return (result);
}

char	*ft_pitoa(unsigned long n)
{
	int				i;
	char			*result;
	unsigned long	temp;

	i = 0;
	temp = n;
	while (n >= 16 && ++i)
		n /= 16;
	result = (char *)malloc(i +2 +2);
	if (!result)
		return (0);
	result[0] = '0';
	result[1] = 'x';
	ft_xitoa_worker(&(result[2]), temp, i + 2, 'x');
	return (result);
}
