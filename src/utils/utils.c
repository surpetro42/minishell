/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:28:58 by surpetro          #+#    #+#             */
/*   Updated: 2024/10/11 15:51:33 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return i;
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	s_len;
	char			*m;
	unsigned int	j;

	if (!s)
		return (NULL);
	i = -1;
	j = 0;
	s_len = ft_strlen(s);
	if (start >= s_len)
		j = 1;
	else if (s_len < len + start)
		j = s_len - start + 1;
	else
		j = len + 1;
	m = malloc(sizeof(char) * j);
	if (m == NULL)
		return (NULL);
	while (++i < j - 1)
		m[i] = s[start + i];
	m[i] = '\0';
	return (m);
}

char	*ft_strstr(char *s1, char *s2)
{
	int i;
	int j;

	if (!*s2)
		return ((char *)s1);
	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (s1[i + j] == s2[j] && s2[j] != '\0')
			j++;
		if (s2[j] == '\0')
			return ((char *)&s1[i]);
		i++;
	}
	return (NULL);
}

int		ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strdup(char *s1)
{
	size_t	i;
	size_t	x;
	char	*m;

	i = 0;
	x = ft_strlen(s1);
	m = (char *)malloc(x + 1);
	if (m == NULL)
		return (NULL);
	while (i < x)
	{
		m[i] = s1[i];
		++i;
	}
	if (i == x)
		m[i] = '\0';
	return (m);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		s1_i;
	int		s2_i;
	char	*con;

	s1_i = 0;
	s2_i = 0;
	con = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!con)
		return (NULL);
	while (s1 && s1[s1_i] != '\0')
	{
		con[s1_i] = s1[s1_i];
		s1_i++;
	}
	while (s2 && s2[s2_i] != '\0')
	{
		con[s1_i] = s2[s2_i];
		s1_i++;
		s2_i++;
	}
	con[s1_i] = '\0';
	if (s1)
		free (s1);
	return (con);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)&s[i]);
		}
		++i;
	}
	if (!c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	x;
	size_t	y;
	char	*m;

	x = 0;
	y = 0;
	if (s1 == NULL)
		return (NULL);
	while (s1[x] && ft_strchr(set, s1[x]) != NULL)
		++x;
	y = ft_strlen(s1);
	while (y > x && ft_strchr(set, s1[y - 1]) != NULL)
		--y;
	m = ft_substr(s1, x, y - x);
	return (m);
}