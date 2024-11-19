/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:47:39 by ayeganya          #+#    #+#             */
/*   Updated: 2024/01/27 15:47:40 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	s_string_count(const char *str, char ch)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if ((!i && str[i] != ch) || (str[i] != ch && str[i - 1] == ch))
			k++;
		i++;
	}
	return (k);
}

static int	sub_str_len(const char *str, char ch)
{
	int	i;

	i = 0;
	while (str[i] != ch && str[i])
		i++;
	return (i);
}

static int	copier(char **ptr, const char *str, int *i, char ch)
{
	int	temp;

	while (str[*i] == ch && str[*i])
		(*i)++;
	temp = sub_str_len(&(str[*i]), ch);
	if (temp)
	{
		*ptr = (char *)malloc(temp + 1);
		if (!(*ptr))
			return (0);
		ft_strlcpy(*ptr, &(str[*i]), temp + 1);
		*i += temp;
		while (str[*i] == ch && str[*i])
			(*i)++;
	}
	else
		while (str[*i] == ch && str[*i])
			(*i)++;
	return (1);
}

static void	cleaner(char **ptr, int j)
{
	j--;
	while (j >= 0)
	{
		free(ptr[j]);
		j--;
	}
	free(ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		j;

	if (!s)
		return (0);
	result = (char **)malloc(sizeof(char *) * (s_string_count(s, c) + 1));
	if (!result)
		return (0);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (!copier(&result[j], s, &i, c))
		{
			cleaner(result, j);
			return (0);
		}
		j++;
	}
	result[s_string_count(s, c)] = 0;
	return (result);
}
