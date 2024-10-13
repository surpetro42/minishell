/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:03:36 by surpetro          #+#    #+#             */
/*   Updated: 2024/10/13 18:16:21 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	collection(char **env)
{
	utils_t	*utils;


	utils->shell = malloc(sizeof(t_shell));
	if(!utils->shell)
		return ;
	utils->shell->duplicate_env = NULL;


	duplicate_env(utils->shell, env);
	while (1)
	{
			pwd(utils);
			echo(str , utils);
			dollar(str, utils);
			env_print(utils);
		// if (ft_strcmp(str, "export") == 0)
		// {
		// 	export_f(utils);
		// }
		// if (ft_strcmp(str, "unset") == 0)
		// ft_execve(shell, env);
	}

}