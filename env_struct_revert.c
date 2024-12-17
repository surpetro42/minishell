/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct_revert.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:33:19 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/09 00:55:53 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int	count_env_elements(t_duplicate_env *duplicate_env)
{
	int	i;

	i = 0;
	while (duplicate_env)
	{
		if (duplicate_env->type == 1)
			i++;
		duplicate_env = duplicate_env->next;
	}
	return (i);
}

int	add_env_elem(t_duplicate_env *duplicate_env, char **env)
{
	int		i;
	char	*temp;

	i = 0;
	while (env[i] != 0)
		i++;
	temp = ft_strjoin(duplicate_env->key, "=");
	if (temp == 0)
		return (1);
	env[i] = ft_strjoin(temp, duplicate_env->value);
	free(temp);
	if (env[i] == 0)
		return (1);
	return (0);
}

int	env_struct_revert(t_utils *utils)
{
	int				size;
	t_duplicate_env	*duplicate_env;

	duplicate_env = utils->shell->duplicate_env;
	if (utils->env != 0)
		clean_argv_memory(utils->env);
	size = count_env_elements(duplicate_env);
	utils->env = (char **)ft_calloc((size + 1), sizeof(char *));
	if (utils->env == 0)
		return (1);
	while (duplicate_env)
	{
		if (duplicate_env->type == 1)
			if (add_env_elem(duplicate_env, utils->env) == 1)
				return (1);
		duplicate_env = duplicate_env->next;
	}
	return (0);
}
