/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:30:33 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/02 21:29:36 by surpetro         ###   ########.fr       */
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
	l = 0;
	x = 0;
	y = 0;
	
	while (str[l] && str[l])
		l++;
	while (l > 0 && str[l] != '$')
		l--;
	while (str[l] && str[l] > 32)
		l++;
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
char	*after(char *str)
{
	int		i;
	int		l;
	int		after_len;
	int		buff;
	char	*s;

	i = 0;
	l = 0;
	after_len = 0;
	while (str && str[i])
		i++;
	while (i > 0)
	{
		if (str[i] == '$')
			break ;
		i--;
	}
	while (str && str[i] > 32)
		i++;
	buff = i;
	while (str[i++])
		after_len++;
	s = malloc(sizeof(char *) * after_len);
	if (!s)
		return (NULL);
	while (str[buff])
		s[l++] = str[buff++];
	s[l] = '\0';
	return (s);
}