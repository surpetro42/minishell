/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 21:58:24 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/12 16:49:45 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishel.h"

char	*current_pwd(t_duplicate_env *env)
{
	while (env)
	{
		if (env->type == 1 && ft_strcmp(env->key, "PWD") == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	pwd(t_utils *utils)
{
	char	cwd[PASS_MAX];

	(void)utils;
	if (getcwd(cwd, PASS_MAX) != NULL)
		printf("%s\n", cwd);
	else
		printf("%s\n", current_pwd(utils->shell->duplicate_env));
}
