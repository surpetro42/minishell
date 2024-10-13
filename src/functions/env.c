/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 23:06:39 by surpetro          #+#    #+#             */
/*   Updated: 2024/10/03 00:10:27 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_print(utils_t *utils)
{
	t_duplicate_env	*start;
	
	start = utils->shell->duplicate_env;
	while(utils->shell->duplicate_env)
	{
		printf("%s=", utils->shell->duplicate_env->key);
		printf("%s\n", utils->shell->duplicate_env->value);	
		utils->shell->duplicate_env = utils->shell->duplicate_env->next;
	}
	utils->shell->duplicate_env = start;
}
