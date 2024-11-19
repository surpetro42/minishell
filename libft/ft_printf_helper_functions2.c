/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:32:52 by ayeganya          #+#    #+#             */
/*   Updated: 2024/02/18 17:32:56 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	str_printer(int *bp, char *str)
{
	int		i;

	i = 0;
	while (str[i] && ++(*bp))
	{
		if (str[i] != -1)
			write(1, &(str[i]), 1);
		else
			write(1, "\0", 1);
		i++;
	}
	return (1);
}

void	char_adder(char *str, char ch)
{
	int	i;

	i = 0;
	while (str[i] != 0)
		i++;
	str[i] = ch;
	str[i +1] = 0;
}

char	*string_former(char *str)
{
	char	*new_str;
	int		size;

	if (str)
	{
		size = ft_strlen(str);
		new_str = (char *)malloc(size +1);
		ft_strlcpy(new_str, str, size +1);
		return (new_str);
	}
	else
	{
		new_str = (char *)malloc(7);
		ft_strlcpy(new_str, "(null)", 7);
	}
	return (new_str);
}
