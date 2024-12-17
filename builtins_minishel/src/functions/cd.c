/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:26:22 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/12 16:49:13 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishel.h"

int	search_fole(t_utils *utils, char *s, char	*cwd)
{
	char	*str;

	str = ft_strdup(s);
	if (str[0] == '-')
		return (minus_oldpwd(utils, cwd, str));
	else if (str[0] == '~' || str[0] < 32)
		return (tilda_oldpwd(utils->shell->duplicate_env, cwd, str));
	else
		return (other(utils->shell->duplicate_env, cwd, str, s));
	return (free(str), 1);
}

int	cd(char *str, t_utils *utils)
{
	char	cwd[PATH_MAX];
	int		res;

	getcwd(cwd, PASS_MAX);
	res = 0;
	if (str)
		res = search_fole(utils, str, cwd);
	else
	{
		home(utils->shell->duplicate_env);
		if (home(utils->shell->duplicate_env) == NULL)
			exit(0);
		res = chdir(home(utils->shell->duplicate_env));
		changes_old_env(&utils->shell->duplicate_env, cwd);
		if (getcwd(cwd, PASS_MAX) == NULL)
			return (1);
		changes_env(&utils->shell->duplicate_env, cwd);
	}
	return (res);
}
