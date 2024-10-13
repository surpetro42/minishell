/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:13:15 by surpetro          #+#    #+#             */
/*   Updated: 2024/09/27 21:08:41 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	access_directory(char *s)
{
	if (access(s, R_OK | X_OK) == 0)
		return (1);
	else
		return (0);
}

char	*home(t_duplicate_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "HOME") == 0)
			return env->value;
		env = env->next;
	}
	return (NULL);
}

int	check_directory(char *s)
{
	struct stat fileStat;

	if(stat(s, &fileStat) < 0)
	{
		printf("minishell: %s: ", s);
		printf("No such file or directory\n");
		return 0;
	}
	return 1;
}

void	changes_old_env(t_duplicate_env **env, char *cwd)
{
	t_duplicate_env *iter;
	
	iter = *env;
	while (*env)
	{
		
		if (ft_strcmp( (*env)->key, "OLDPWD") == 0)
		{
			free((*env)->value); 
			(*env)->value = ft_strdup(cwd);
		}
		*env = (*env)->next;
	}
	*env = iter;
}

void	changes_env(t_duplicate_env **env, char *cwd)
{
	t_duplicate_env *iter;
	
	iter = *env;
	while (*env)
	{
		if(ft_strcmp( (*env)->key, "PWD") == 0)
		{
			free((*env)->value); 
			(*env)->value = ft_strdup(cwd);
		}
		*env = (*env)->next;
	}
	*env = iter;
}
