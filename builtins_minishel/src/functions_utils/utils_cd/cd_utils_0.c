/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:13:15 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/09 23:31:51 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishel.h"

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
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	check_directory(char *s)
{
	struct stat	file_stat;

	if (stat(s, &file_stat) < 0)
	{
		write(2, "minishell: cd: ", 15);
		write(2, s, ft_strlen(s));
		write(2, ": No such file or directory\n", 28);
		return (0);
	}
	if (!S_ISDIR(file_stat.st_mode))
	{
		write(2, "minishell: cd: ", 15);
		write(2, s, ft_strlen(s));
		write(2, ": Is not a directory\n", 21);
		return (0);
	}
	return (1);
}

void	changes_old_env(t_duplicate_env **env, char *cwd)
{
	t_duplicate_env	*iter;

	iter = *env;
	while (*env)
	{
		if ((*env)->type == 1 && (ft_strcmp ((*env)->key, "OLDPWD")) == 0)
		{
			if ((*env)->value != NULL)
				free((*env)->value);
			if (cwd != 0)
				(*env)->value = ft_strdup(cwd);
			else
				(*env)->value = 0;
		}
		*env = (*env)->next;
	}
	*env = iter;
}

void	changes_env(t_duplicate_env **env, char *cwd)
{
	t_duplicate_env	*iter;

	iter = *env;
	while (*env)
	{
		if (ft_strcmp((*env)->key, "PWD") == 0)
		{
			free((*env)->value);
			(*env)->value = ft_strdup(cwd);
		}
		*env = (*env)->next;
	}
	*env = iter;
}
