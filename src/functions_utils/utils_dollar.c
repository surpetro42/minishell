/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:13:15 by surpetro          #+#    #+#             */
/*   Updated: 2024/10/11 16:11:22 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup(char *s1)
{
	int		i;
	int		x;
	char	*m;

	i = 0;
	x = 0;
	if(s1[i] == '$')
		i++;
	while (s1[x])
	{
		if(s1[x] == '$')
			break;
		x++;
	}
	i = 0;
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
