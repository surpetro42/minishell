/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:04:34 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/02 18:19:05 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishel.h"

char	*variable(char *str)
{
	int		i;
	int		l;
	int		buff;
	char	*res;

	i = 0;
	l = 0;
	if(str[i] == '$')
	{
		i++;
		if(str[i] >= '0' && str[i] <= '9')
			i++;
		return str;
	}
	buff = i;
	while (str[buff])
		buff++;
	res = malloc(sizeof(char *) * buff + 1);
	if(!res)
		return  (NULL);
	while (str[i])
		res[l++] = str[i++];
	res[l] = '\0';
	
	return (res);
}

char	*remains(char *key)
{
	char	*str;

	int	i;
	int	l;
	int	len;

	i = 1;
	l = 0;
	while (key[i])
	{
		if(key[i] == '$')
			break;
		if (key[i] && ((key[i] >= 'a' && key[i] <= 'z')
			|| (key[i] >= 'A' && key[i] <= 'Z')
			|| (key[i] >= '0' && key[i] <= '9') || key[i] == '_'))
			i++;
		else
			break;
	}
	len = ft_strlen(&key[i]);
	str = malloc(sizeof(char *) * len + 1);
	while (key[i])
	{
		if(key[i] == '$')
			break;
		str[l++] = key[i++];
	}
	str[l] = '\0';
	return str;
}

int	valid_remains_line(char *str)
{
	if (((str[0] >= 'a' && str[0] <= 'z')
		|| (str[0] >= 'A' && str[0] <= 'Z')
		|| (str[0] >= '0' && str[0] <= '9') || str[0] == '_'))
		return 0;
	return (1);
}
