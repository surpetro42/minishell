/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 22:20:10 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/10 18:13:05 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishel.h"

void	no_valid_unset(char *str)
{
	write(2, "bash: unset: ", 13);
	write(2, str, ft_strlen(str));
	write(2, ": not a valid identifier\n", 25);
}

int	unset_f(t_utils *utils, char **str)
{
	t_duplicate_env	*start;
	int				i;

	i = 1;
	start = utils->shell->duplicate_env;
	if (str[1])
	{
		while (str[i])
		{
			if (validation_symble_variable(str[i]) == 0)
			{
				no_valid_unset(str[i]);
				return (1);
			}
			while (utils->shell->duplicate_env)
			{
				if (ft_strcmp(utils->shell->duplicate_env->key, str[i]) == 0)
					utils->shell->duplicate_env->type = 0;
				utils->shell->duplicate_env = utils->shell->duplicate_env->next;
			}
			utils->shell->duplicate_env = start;
			i++;
		}
	}
	return (env_struct_revert (utils));
}
