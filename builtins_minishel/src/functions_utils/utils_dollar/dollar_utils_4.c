/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 02:49:43 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/10 04:33:07 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishel.h"

void	doll_key_after(t_var_dollar *var, char *str)
{
	var->s2_key = key(str);
	var->s3_after = after(str);
}

void	doll_before_key_after(t_var_dollar *var, char *str)
{
	var->s1_before = before_dollar(str);
	var->s2_key = key(str);
	var->s3_after = after(str);
}

char	*share_dollar_input(t_var_dollar *var, char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	if (str[i] == '$')
		doll_key_after(var, str);
	if (count > 0 && str[i] != '$')
		doll_before_key_after(var, str);
	else
	{
		var->s1_before = before_dollar(str);
		return (var->s1_before);
	}
	return (NULL);
}

char	*opn_ext_sts(int last_exit_status)
{
	char	*s;

	s = NULL;
	s = ft_itoa(last_exit_status);
	return (s);
}
