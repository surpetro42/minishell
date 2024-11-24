/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:57:25 by surpetro          #+#    #+#             */
/*   Updated: 2024/11/22 18:04:13 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishel.h"

int	validation_symble_variable(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s) - 1;
	if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
		|| s[i] == '_' )
	{
		while (s[++i] && s[i] != '=')
		{
			if (!((s[i] >= 'a' && s[i] <= 'z')
					|| (s[i] >= 'A' && s[i] <= 'Z')
					|| (s[i] >= '0' && s[i] <= '9') || s[i] == '_'))
				return (0); 
		}
	}
	else
	{
		printf("minishell: expoer: command not found\n");
		return (0);
	}
	return (1);
}

int	find_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

int	find_before_equal(char *s)
{
	int	i;

	i = 0;
	while (s[0] != '=' && s[i] > 32)
	{
		if (s[i] == '=')
		{
			i++;
			return (i);
		}
		i++;
	}
	return (i);
}

int	validation_equal_variable(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
