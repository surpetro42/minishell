/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:04:34 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/10 03:55:11 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishel.h"

//		part initialization variable dollar
void	initialization(t_var_dollar *var)
{
	var->buff = NULL;
	var->res_1 = NULL;
	var->res_line_key = NULL;
	var->s1_before = NULL;
	var->s2_key = NULL;
	var->s3_after = NULL;
	var->res_buff = NULL;
	var->line = NULL;
	var->res_line = NULL;
	var->res_line_remains = NULL;
	var->open_exit_status = NULL;
}

int	key_search_env(t_duplicate_env duplicate_env, t_var_dollar *var)
{
	int		value_len;

	value_len = 0;
	if (ft_strcmp(var->buff, duplicate_env.key) == 0)
	{
		var->res_buff = ft_strdup(duplicate_env.value);
		if (!var->res_buff)
			return (0);
		return (1);
	}
	return (0);
}

void	env_list_key_search(t_duplicate_env **duplicate_env, t_var_dollar *var)
{
	while (*duplicate_env)
	{
		if (key_search_env(**duplicate_env, var) == 1)
			break ;
		*duplicate_env = (*duplicate_env)->next;
	}
	if (var->buff != 0)
		free(var->buff);
}

int	take_key(char *key, t_var_dollar *var)
{
	char	*temp;

	temp = ft_strndup(key);
	var->buff = ft_strtrim(temp, " ");
	free(temp);
	if (dollar_validation(var->buff) == 0)
	{
		free(var->buff);
		var->buff = 0;
		return (1);
	}
	return (0);
}
