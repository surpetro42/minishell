/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:30:33 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/10 04:29:54 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishel.h"

//		part -> before the dollar sign
char	*before_dollar(char *str)
{
	int		i;
	int		l;
	char	*s;

	i = 0;
	l = 0;
	while (str && str[i] && str[i] != '$')
		i++;
	s = malloc(sizeof(char *) * i + 1);
	if (!s)
		return (NULL);
	while (str[l] && str[l] != '$')
	{
		if (str[l] == -15)
			s[l++] = '$';
		s[l] = str[l];
		l++;
	}
	if (l == i)
		s[l] = '\0';
	return (s);
}

//		part -> The words after the dollar sign

char	*key(char *str)
{
	int		i;
	int		l;
	int		x;
	int		y;
	char	*s;

	i = 0;
	x = 0;
	y = 0;
	l = search_symbol_dollar(str, 0);
	while (str[i] && str[i] != '$')
		i++;
	x = l - i;
	s = malloc(sizeof(char *) * x + 1);
	while (i < l)
	{
		s[y] = str[i];
		y++;
		i++;
	}
	s[y] = '\0';
	return (s);
}

//		part -> after the dollar sign
int	after_dollar_symbol(char *str, int i)
{
	i = ft_strlen(str);
	while (i > 0)
	{
		if (str[i] == '$')
			break ;
		i--;
	}
	while (str && str[i] > 32)
		i++;
	return (i);
}

void	copying_after(char *str, char *s, int buff)
{
	int	i;

	i = 0;
	while (str[buff])
	{
		if (str[buff] == -15)
		{
			s[i++] = '$';
			buff++;
		}
		if (str[buff])
			s[i++] = str[buff++];
	}
	s[i] = '\0';
}

char	*after(char *str)
{
	int		i;
	int		buff;
	int		after_len;
	char	*s;

	after_len = 0;
	s = NULL;
	i = after_dollar_symbol(str, 0);
	buff = i;
	while (str[i++])
		after_len++;
	s = malloc(sizeof(char *) * after_len);
	if (!s)
		return (NULL);
	copying_after(str, s, buff);
	return (s);
}
