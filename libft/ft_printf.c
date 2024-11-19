/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:08:40 by ayeganya          #+#    #+#             */
/*   Updated: 2024/02/09 16:12:03 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		sc_processor(char type, int *index, int *bp, va_list args_copy);
int		p_sgn_extract(const char *str, int *index, int *bp, va_list args_copy);
int		sgn_processor(const char *str, int *index, int *bp, va_list args_copy);
int		align_prcsr(const char *str, int *index, int *bp, va_list args_copy);

int	dispatcher(const char *str, int *index, int *bp, va_list args_copy)
{
	int	result;

	if (*str == 'c' || *str == 'd' || *str == 'i' || *str == 'u' \
	|| *str == 'x' || *str == 'X' || *str == 'p' || *str == 's')
		result = sc_processor(*str, index, bp, args_copy);
	else if (*str == '#')
		result = p_sgn_extract(str, index, bp, args_copy);
	else if (*str == ' ' || *str == '+')
		result = sgn_processor(str, index, bp, args_copy);
	else if (*str == '-' || *str == '0' || *str == '.' || \
	(*str >= '1' && *str <= '9'))
		result = align_prcsr(str, index, bp, args_copy);
	else
	{
		result = 1;
		(*index)++;
	}
	return (result);
}

static int	string_iterator(const char *str, int *i, int *j, va_list args)
{
	va_list	args_copy;

	while (str[*i])
	{
		if (str[*i] == '%' && str[*i + 1] != '%')
		{
			va_copy(args_copy, args);
			if (dispatcher(&str[++(*i)], i, j, args_copy) == -1)
				return (-1);
			va_arg(args, char *);
		}
		else if (str[*i] == '%' && str[*i + 1] == '%')
		{
			write(1, "%", 1);
			(*i) += 2;
			(*j)++;
		}
		else if (++(*j))
			write(1, &str[(*i)++], 1);
	}
	va_end(args);
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		j;
	va_list	args;

	if (!str)
		return (-1);
	i = 0;
	j = 0;
	va_start(args, str);
	if (string_iterator(str, &i, &j, args) == -1)
		return (-1);
	return (j);
}
