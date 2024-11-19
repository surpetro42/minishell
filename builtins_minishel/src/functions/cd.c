/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:26:22 by surpetro          #+#    #+#             */
/*   Updated: 2024/11/12 18:10:00 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishel.h"


// dzelu ban ka

int	search_fole(t_duplicate_env *env, char *s)
{
	char cwd[PATH_MAX];
	char *str;

	if (getcwd(cwd, PASS_MAX) == NULL)
		return 0;
	str = ft_strdup(s);
	if (str[0] == '-')
	{
		if (old_environment(env) == NULL)
			exit(0);
		chdir(old_environment(env));
		getcwd(cwd, PATH_MAX);
		changes_env(&env, cwd);
		return 1;
	}
	else if (str[0] == '~' || str[0] < 32)
	{
		changes_old_env(&env, cwd);
		if (home(env) == NULL)
			exit(0);
		chdir(home(env));
		getcwd(cwd, PATH_MAX);
		changes_env(&env, cwd);
		return 1;
	}
	else
	{
		if (check_directory(str) == 0)
			return 0;
		if (access_directory(str) == 0)
		{
			printf("minishell: %s: ", s);
			printf("Permission denied\n");
			return 0;
		}
		changes_old_env(&env, cwd);
		chdir(str);
		getcwd(cwd, PATH_MAX);
		changes_env(&env, cwd);
		return 1;
	}
	return 0;
}

int		cd(char *str, utils_t *utils)
{
	int res = 0;

	if(str)
		res = search_fole(utils->shell->duplicate_env, str);
	else
	{
		home(utils->shell->duplicate_env);
		if (home(utils->shell->duplicate_env) == NULL)
			exit(0);
		res = chdir(home(utils->shell->duplicate_env));
	}
	return res;
}
