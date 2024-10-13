/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:26:22 by surpetro          #+#    #+#             */
/*   Updated: 2024/10/07 20:14:53 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


// dzelu ban ka 




int	search_fole(t_duplicate_env *env, char *s)
{
	char cwd[PATH_MAX];
	char *str;

	if (getcwd(cwd, PASS_MAX) == NULL)
		return 0;
	str = ft_strdup(s);
	if (str[0] == '~' || str[0] < 32)
	{
		changes_old_env(&env, cwd);
		if (home(env) == NULL)
			exit(0);
		chdir(home(env));
		getcwd(cwd, PATH_MAX);
		changes_env(&env, cwd);
		return 1;
	}
	else if(str[0] > 32)
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
	int i = 0;
	int buff = 0;
	int res = 0;

	while (str[i])
	{
		if (str[i] == 'c' && str[i + 1] == 'd' && str[i + 2] == ' ')
		{
			buff = i;
			buff += 3;
			res = search_fole(utils->shell->duplicate_env, &str[buff]);
		}
		else if (str[i] == 'c' && str[i + 1] == 'd' && str[i + 2] <=  32)
		{
			home(utils->shell->duplicate_env);
			if (home(utils->shell->duplicate_env) == NULL)
				exit(0);
			res = chdir(home(utils->shell->duplicate_env));
		}
		else if (str[i] == 'c' && str[i + 1] == 'd' && str[i + 2] > 32)
			printf("command not found\n");
		i++;
	}
	return res;
}
