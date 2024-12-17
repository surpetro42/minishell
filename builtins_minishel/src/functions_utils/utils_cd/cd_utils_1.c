/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:13:15 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/12 16:50:08 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishel.h"

int	minus_oldpwd(t_utils *utils, char *cwd, char *str)
{
	if (old_environment(utils->shell->duplicate_env) == NULL)
		return (1);
	chdir(old_environment(utils->shell->duplicate_env));
	getcwd(cwd, PATH_MAX);
	changes_env(&utils->shell->duplicate_env, cwd);
	pwd(utils);
	return (free(str), 0);
}

int	tilda_oldpwd(t_duplicate_env *env, char *cwd, char *str)
{
	changes_old_env(&env, cwd);
	if (home(env) == NULL)
		return (free(str), 1);
	chdir(home(env));
	getcwd(cwd, PATH_MAX);
	changes_env(&env, cwd);
	return (free(str), 0);
}

int	other(t_duplicate_env *env, char *cwd, char *str, char *s)
{
	if (check_directory(str) == 0)
		return (free(str), 1);
	if (access_directory(str) == 0)
	{
		write(2, "minishell: cd: ", 15);
		write(2, s, ft_strlen(s));
		write(2, ": Permission denied\n", 20);
		return (free(str), 1);
	}
	changes_old_env(&env, cwd);
	chdir(str);
	getcwd(cwd, PASS_MAX);
	changes_env(&env, cwd);
	return (free(str), 0);
}

char	*old_environment(t_duplicate_env *env)
{
	while (env)
	{
		if (env->type == 1 && ft_strcmp(env->key, "OLDPWD") == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
