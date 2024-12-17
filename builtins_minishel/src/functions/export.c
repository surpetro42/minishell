/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 22:19:45 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/10 19:11:33 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishel.h"

int	input_export(t_duplicate_env *env, char **str)
{
	t_duplicate_env	*start;
	t_duplicate_env	*last;
	t_var_export	var;
	int				i;

	i = 0;
	start = env;
	last = env;
	while (last && last->next)
		last = last->next;
	while (str[i])
	{
		if (arr_string_element(str[i], &start, &last, &var) == 0)
		{
			write(2, "minishell: export: ", 19);
			write(2, str[i], ft_strlen(str[i]));
			write(2, ": not a valid identifier\n", 25);
			free_export(var);
			return (1);
		}
		free_export(var);
		i++;
	}
	env = start;
	return (0);
}

int	export_f(t_utils *utils, char **str)
{
	t_duplicate_env	*start;
	int				i;
	int				exit_status;

	i = 0;
	exit_status = 0;
	start = utils->shell->duplicate_env;
	if (str[1])
	{
		exit_status = input_export(utils->shell->duplicate_env, &str[1]);
		if (exit_status == 0)
			exit_status = env_struct_revert(utils);
	}
	else if (str[0] && !str[1])
	{
		add_enviorment(utils->shell);
		ft_env_elem_sort(&utils->shell->input_export, ft_strcmp);
		print_export_list(utils);
	}
	return (exit_status);
}
