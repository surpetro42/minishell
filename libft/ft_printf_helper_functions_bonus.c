/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_helper_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:37:14 by ayeganya          #+#    #+#             */
/*   Updated: 2024/02/18 17:37:16 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	char_adder(char *str, char ch);
void	extractor(char type, va_list args_copy, char **result);

char	*string_expander_0(char *str, int len)
{
	int		str_size;
	int		min_case;
	char	*temp;

	min_case = 0;
	str_size = ft_strlen(str);
	temp = (char *)ft_calloc(len + 2, 1);
	if (!temp)
		return (0);
	if (*str == '-' && ++min_case)
	{
		str = str +1;
		char_adder(temp, '-');
	}
	while (str_size < len && ++str_size)
		char_adder(temp, '0');
	ft_strlcat(temp, str, len + 1);
	if (min_case)
		free(str -1);
	else
		free(str);
	return (temp);
}

char	*string_expander(char *str, int len, char ch)
{
	int		str_size;
	char	*temp;

	if (ch == '0')
		return (string_expander_0(str, len));
	temp = (char *)ft_calloc(len + 1, 1);
	if (!temp)
		return (0);
	str_size = ft_strlen(str);
	if (ch < 0)
	{
		ch = -ch;
		ft_strlcpy(temp, str, len + 1);
		while (str_size < len && ++str_size)
			char_adder(temp, ch);
	}
	else
	{
		while (str_size < len && ++str_size)
			char_adder(temp, ch);
		ft_strlcat(temp, str, len + 1);
	}
	free (str);
	return (temp);
}

char	*string_expander_dot_0(char *str, int len)
{
	int		str_size;
	int		min_case;
	char	*temp;

	min_case = 0;
	str_size = ft_strlen(str);
	temp = (char *)ft_calloc(len + 2, 1);
	if (!temp)
		return (0);
	if (*str == '-' && ++len && ++min_case)
	{
		str = str +1;
		char_adder(temp, '-');
	}
	while (str_size < len && ++str_size)
		char_adder(temp, '0');
	ft_strlcat(temp, str, len + 1);
	if (min_case)
		free(str -1);
	else
		free(str);
	return (temp);
}

void	get_format2(const char *str, int *index, t_align *f, va_list args_copy)
{
	int		i;
	char	*temp;

	i = 0;
	if (str[i] == '.' && ++i && ++(*index))
	{
		f->d_numb = ft_atoi(&(str[i]));
		while (ft_isdigit(str[i]) && ++(*index))
			i++;
	}
	f->l_ltr = str[i];
	++(*index);
	extractor(f->l_ltr, args_copy, &temp);
	if (!temp)
	{
		f->f_sign = -2;
		return ;
	}
	if (f->d_numb == 0 && *temp == '0')
		f->d_numb = -2;
	free(temp);
	if (f->d_numb != -1 && f->f_sign == 0)
		f->f_sign = 1;
}

void	get_format(const char *str, int *index, t_align *f, va_list args_copy)
{
	int	i;

	i = 0;
	f->f_sign = 1;
	f->f_numb = -1;
	f->d_numb = -1;
	while ((str[i] == '-' || str[i] == '0') && ++(*index))
	{
		if (str[i] == '-')
			f->f_sign = -1;
		if (str[i] == '0' && f->f_sign != -1)
			f->f_sign = 0;
		i++;
	}
	if (ft_isdigit(str[i]))
	{
		f->f_numb = ft_atoi(&(str[i]));
		while (ft_isdigit(str[i]) && ++(*index))
			i++;
	}
	get_format2(&(str[i]), index, f, args_copy);
}
