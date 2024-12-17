/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 04:33:10 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/10 04:40:50 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishel.h"

int	search_symbol_dollar(char *str, int l)
{
	while (str[l] && str[l])
		l++;
	while (l > 0 && str[l] != '$')
		l--;
	while (str[l] && str[l] > 32)
		l++;
	return (l);
}

int	find_remains_end(char *key, int i)
{
	while (key[i])
	{
		if (key[i] == '$')
			break ;
		if (key[i] && ((key[i] >= 'a' && key[i] <= 'z')
				|| (key[i] >= 'A' && key[i] <= 'Z')
				|| (key[i] >= '0' && key[i] <= '9') || key[i] == '_'))
			i++;
		else
			break ;
	}
	return (i);
}
