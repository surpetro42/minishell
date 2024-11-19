/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operand_processors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:19:40 by ayeganya          #+#    #+#             */
/*   Updated: 2024/02/12 12:19:42 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		str_printer(int *bp, char *str);
int		dispatcher(const char *str, int *index, int *bp, va_list args_copy);
int		sc_processor(char type, int *index, int *bp, va_list args_copy);
char	*ft_uitoa(unsigned int n);
char	*ft_xitoa(unsigned long n, char cap);
char	*ft_pitoa(unsigned long n);
char	*string_former(char *str);

void	extractor(char type, va_list args_copy, char **result)
{
	if (type == 'd' || type == 'i')
		*result = ft_itoa(va_arg(args_copy, int));
	else if (type == 'u')
		*result = ft_uitoa(va_arg(args_copy, unsigned int));
	else if (type == 'X' || type == 'x')
		*result = ft_xitoa(va_arg(args_copy, unsigned int), type);
	else if (type == 'p')
		*result = ft_pitoa((unsigned long)va_arg(args_copy, void *));
	else if (type == 's')
		*result = string_former(va_arg(args_copy, char *));
	else if (type == 'c')
	{
		*result = (char *)malloc(2);
		**result = (char)va_arg(args_copy, int);
		(*result)[1] = 0;
		if (**result == 0)
			**result = -1;
	}
	else
		va_arg(args_copy, char *);
	va_end(args_copy);
}

int	sc_processor(char type, int *index, int *bp, va_list args_copy)
{
	char	*sub_str;

	(*index)++;
	extractor(type, args_copy, &sub_str);
	if (!sub_str)
		return (-1);
	str_printer(bp, sub_str);
	free (sub_str);
	return (1);
}

int	p_sgn_prcsr(const char *str, int *index, int *bp, unsigned int nbr)
{
	int		i;
	char	*sub_str;

	(*index)++;
	sub_str = ft_xitoa(nbr, *(str +1));
	if (!sub_str)
		return (-1);
	i = ft_strlen(sub_str);
	if (*sub_str != '0')
	{
		write(1, "0", 1);
		write(1, str + 1, 1);
		(*bp) += i + 2;
	}
	else
		(*bp)++;
	write(1, sub_str, i);
	(*index)++;
	free (sub_str);
	return (1);
}

int	p_sgn_extract(const char *str, int *index, int *bp, va_list args_copy)
{
	unsigned int	nbr;

	if (*(str +1) == 'X' || *(str +1) == 'x')
	{
		nbr = va_arg(args_copy, unsigned int);
		va_end(args_copy);
		return (p_sgn_prcsr(str, index, bp, nbr));
	}
	else
		return (dispatcher(str +1, index, bp, args_copy));
}

int	sgn_processor(const char *str, int *index, int *bp, va_list args_copy)
{
	int			nbr;
	va_list		args_copy_copy;
	const char	temp = 'd';

	(*index)++;
	if (*(str +1) == 'd' || *(str +1) == 'i')
	{
		va_copy(args_copy_copy, args_copy);
		nbr = va_arg(args_copy_copy, int);
		va_end(args_copy_copy);
		if (nbr < 0)
			return (sc_processor(temp, index, bp, args_copy));
		else
		{
			if (*str == ' ')
				write(1, " ", 1);
			else
				write(1, "+", 1);
			(*bp)++;
			return (sc_processor(str[1], index, bp, args_copy));
		}
	}
	else
		return (dispatcher(str +1, index, bp, args_copy));
}
