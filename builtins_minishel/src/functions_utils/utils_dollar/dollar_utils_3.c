/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:04:34 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/04 22:31:13 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishel.h"

int	key_search_env(t_duplicate_env duplicate_env, t_var_dollar *var)
{
	int	value_len;

	value_len = 0;
	if (ft_strcmp(var->buff, duplicate_env.key) == 0)
	{
		value_len = ft_strlen(duplicate_env.value);
		var->res_buff = malloc(sizeof(char *) * value_len);
		if (!var->res_buff)
			return (0);
		var->res_buff = ft_strdup(duplicate_env.value); 
		return (1);
	}
	return (0);
}

void	env_list_key_search(t_duplicate_env **duplicate_env, t_var_dollar *var)
{
	while (*duplicate_env)
	{
		if(key_search_env(**duplicate_env, var) == 1)
			break;
		*duplicate_env = (*duplicate_env)->next;
	}
}

int		take_key(char *key, int i, t_var_dollar *var)
{
	var->buff = ft_strndup(&key[i]);
	var->buff = ft_strtrim(var->buff, " ");
	if (dollar_validation(var->buff) == 0)
	{
		free(var->buff);
		return (1);
	}	
	return (0);
}
