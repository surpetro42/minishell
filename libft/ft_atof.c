/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:22:10 by ayeganya          #+#    #+#             */
/*   Updated: 2024/06/06 15:29:25 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long double	pow(long double base, int exp)
{
	int			i;
	int			sign;
	long double	result;

	i = 0;
	result = 1;
	sign = 0;
	if (exp < 0 && ++sign)
		exp = -exp;
	while (i < exp && ++i)
		result *= base;
	if (sign)
		result = 1 / result;
	return (result);
}

long double	ft_atof(const char *str)
{
	int			i;
	int			j;
	long double	result;
	int			sign;

	i = 0;
	j = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\v' \
	|| str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (++i && str[i - 1] == '-')
			sign *= -1;
	if (ft_isdigit(str[i]))
		result = str[i] - '0';
	else
		return (0);
	i++;
	while (ft_isdigit(str[i]) && ++i)
		result = result * 10 + str[i - 1] - '0';
	if (str[i] == '.' && ++i)
		while (ft_isdigit(str[i]) && ++i && ++j)
			result = result + (str[i - 1] - '0') / pow(10, j);
	return (result * sign);
}
