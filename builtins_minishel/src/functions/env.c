/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 23:06:39 by surpetro          #+#    #+#             */
/*   Updated: 2024/11/19 00:56:57 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishel.h"

void	env_print(utils_t *utils)
{
	t_duplicate_env	*start;
	
	start = utils->shell->duplicate_env;

	while (utils->shell->duplicate_env)
	{
		if (ft_strlen(utils->shell->duplicate_env->value) != 0 && utils->shell->duplicate_env->value != NULL && utils->shell->duplicate_env->type != 0)
		{
			if (utils->shell->duplicate_env->key)
				printf("%s=", utils->shell->duplicate_env->key);
			if (utils->shell->duplicate_env->value)
				printf("%s\n", utils->shell->duplicate_env->value);
		}
		utils->shell->duplicate_env = utils->shell->duplicate_env->next;
	}
	utils->shell->duplicate_env = start;
}
