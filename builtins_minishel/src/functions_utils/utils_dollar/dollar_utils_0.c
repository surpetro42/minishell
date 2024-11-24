/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:13:15 by surpetro          #+#    #+#             */
/*   Updated: 2024/11/22 20:58:44 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishel.h"

char	*ft_strndup(char *s1)
{
	int		i;
	int		x;
	char	*m;

	x = 0;
	while(s1[x] == '$')
		x++;
	while (s1[x])
	{
		if(s1[x] == '$')
			break ;
		if (!((s1[x] >= 'a' && s1[x] <= 'z')
			|| (s1[x] >= 'A' && s1[x] <= 'Z')
			|| (s1[x] >= '0' && s1[x] <= '9') || s1[x] == '_'))
			break ;
		x++;
	}
	m = (char *)malloc(x + 1);
	if (m == NULL)
		return (NULL);
	i = -1;
	while (++i < x)
		m[i] = s1[i];
	if (i == x)
		m[i] = '\0';
	return (m);
}

//		part_validation_key
int	dollar_validation(char *s)
{
	int	i;

	i = 0;
	if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
		|| (s[i] >= '0' && s[i] <= '9') || s[i] == '_' )
	{
		i++;
		while (s[i])
		{
			if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
				|| (s[i] >= '0' && s[i] <= '9') || s[i] == '_'))
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

//		part $?
char	*completion_status(char *str, int last_exit_status)
{
	char	*s;

	s = NULL;
	if(str[0] == '$' && str[1] == '?')
		s = ft_itoa(last_exit_status);
	return s;
}