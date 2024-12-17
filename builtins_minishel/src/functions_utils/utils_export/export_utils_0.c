/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:57:25 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/10 05:24:04 by surpetro         ###   ########.fr       */
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
		return (0);
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

void	new_nudd_list(t_var_export *var, int len_equally)
{
	if (var->buff_vlaue && var->buff_vlaue[0])
		var->new_node = create_new_node(ft_substr
				(var->buff_key, 0, var->findel - 1),
				ft_strdup(var->buff_vlaue), 1);
	else if (var->buff_key[len_equally] == '=')
		var->new_node = create_new_node(ft_substr
				(var->buff_key, 0, var->findel - 1),
				"", 1);
	else
		var->new_node = create_new_node(ft_substr
				(var->buff_key, 0, var->findel - 1),
				NULL, 1);
}
