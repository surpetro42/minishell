/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operand_processors2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:25:32 by ayeganya          #+#    #+#             */
/*   Updated: 2024/02/12 14:25:35 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		str_printer(int *bp, char *str);
char	*string_expander(char *str, int len, char ch);
char	*string_expander_dot_0(char *str, int len);
void	get_format(const char *str, int *index, t_align *f, va_list args_copy);
void	extractor(char type, va_list args_copy, char **result);

int	algn_3(t_align *f, int *bp, char *str)
{
	char	mode;

	mode = f->f_sign;
	mode *= ' ';
	if (str && (int)ft_strlen(str) > f->d_numb)
		str[f->d_numb] = 0;
	if (str && (int)ft_strlen(str) < f->f_numb && f->f_numb != 0)
		str = string_expander(str, f->f_numb, mode);
	if (!str)
		return (-1);
	str_printer(bp, str);
	free (str);
	return (1);
}

int	algn_2(t_align *f, int *bp, char *str)
{
	char	*str_cpy;
	char	mode;
	int		sz;

	mode = f->f_sign;
	mode *= ' ';
	sz = (int)ft_strlen(str);
	str_cpy = str;
	if (str && (sz < f->d_numb || (*str == '-' && sz -1 < f->d_numb)))
	{
		str = string_expander_dot_0(str, f->d_numb);
		sz = (int)ft_strlen(str);
	}
	if (str && sz < f->f_numb && f->f_numb != 0)
		str = string_expander(str, f->f_numb, mode);
	if (!str)
	{
		free(str_cpy);
		return (-1);
	}
	str_printer(bp, str);
	free (str);
	return (1);
}

int	algn_1(t_align *f, int *bp, char *str)
{
	char	*str_cpy;
	char	mode;

	mode = f->f_sign;
	mode *= ' ';
	if (mode == 0)
		mode = '0';
	str_cpy = str;
	if (str && (int)ft_strlen(str) < f->f_numb)
		str = string_expander(str, f->f_numb, mode);
	if (!str)
	{
		free(str_cpy);
		return (-1);
	}
	str_printer(bp, str);
	free (str);
	return (1);
}

int	align_prcsr(const char *str, int *index, int *bp, va_list args_copy)
{
	t_align	f;
	va_list	args_copy_copy;
	char	*sub_str;

	va_copy(args_copy_copy, args_copy);
	get_format(str, index, &f, args_copy_copy);
	extractor(f.l_ltr, args_copy, &sub_str);
	if (!sub_str || f.f_sign == -2)
		return (-1);
	if (f.d_numb == -2)
		*sub_str = 0;
	if (f.d_numb < 0 && f.f_numb >= 0)
		return (algn_1(&f, bp, sub_str));
	else if (f.d_numb < 0 && f.f_numb == -1 && str_printer(bp, sub_str))
	{
		free(sub_str);
		return (1);
	}
	else if (f.d_numb >= 0 && f.l_ltr != 's' && f.l_ltr != 'c')
		return (algn_2(&f, bp, sub_str));
	else if (f.d_numb >= 0 && (f.l_ltr == 's' || f.l_ltr == 'c'))
		return (algn_3(&f, bp, sub_str));
	else
		return (1);
}
