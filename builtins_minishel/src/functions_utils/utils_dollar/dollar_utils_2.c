/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:04:34 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/10 04:39:49 by surpetro         ###   ########.fr       */
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
	if (str[i] == '$')
	{
		i++;
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		return (str);
	}
	buff = i;
	while (str[buff])
		buff++;
	res = malloc(sizeof(char *) * buff + 1);
	if (!res)
		return (NULL);
	while (str[i])
		res[l++] = str[i++];
	res[l] = '\0';
	return (res);
}

char	*remains(char *key)
{
	int		i;
	int		l;
	int		len;
	char	*str;

	l = 0;
	i = find_remains_end(key, 1);
	len = ft_strlen(&key[i]);
	str = malloc(sizeof(char *) * len + 1);
	while (key[i])
	{
		if (key[i] == '$')
			break ;
		str[l++] = key[i++];
	}
	str[l] = '\0';
	return (str);
}

int	valid_remains_line(char *str)
{
	if (((str[0] >= 'a' && str[0] <= 'z')
			|| (str[0] >= 'A' && str[0] <= 'Z')
			|| (str[0] >= '0' && str[0] <= '9') || str[0] == '_'))
		return (0);
	return (1);
}

int	search_for_a_negative_character(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < 0)
			return (1);
		i++;
	}
	return (0);
}

char	*development_s3_atfer(char *str)
{
	int		i;
	int		l;
	int		len;
	char	*buff;

	i = 0;
	l = 0;
	len = ft_strlen(str);
	buff = malloc(sizeof(char *) * len + 1);
	if (!buff)
		return (NULL);
	while (str[i])
	{
		if (str[i] < 0)
			i++;
		buff[l] = str[i];
		if (str[i])
			i++;
		l++;
	}
	buff[i] = '\0';
	free(str);
	return (buff);
}
