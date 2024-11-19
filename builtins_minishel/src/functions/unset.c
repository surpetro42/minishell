/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 22:20:10 by surpetro          #+#    #+#             */
/*   Updated: 2024/11/11 19:08:37 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishel.h"

void	unset_f(utils_t *utils, char **str)
{
	t_duplicate_env	*start;
	int i;

	i = 1;
	start = utils->shell->duplicate_env;
	if(str[1])
	{
		while (str[i])
		{		
			while (utils->shell->duplicate_env)
			{
				if(ft_strcmp(utils->shell->duplicate_env->key, str[i]) == 0)
				{
					utils->shell->duplicate_env->type = 0;
				}
				utils->shell->duplicate_env = utils->shell->duplicate_env->next;
			}
			utils->shell->duplicate_env = start;
			i++;
		}
	}
}
