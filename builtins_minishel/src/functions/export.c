/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 22:19:45 by surpetro          #+#    #+#             */
/*   Updated: 2024/11/24 22:44:53 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishel.h"

void	input_export(t_duplicate_env *env, char **str)
{
	t_duplicate_env	*start;
	t_duplicate_env	*last;
	int		i;

	i = 0;
	start = env;
	last = env;

	while (last && last->next)
		last = last->next;

	while (str[i])
	{
		if(arr_string_element(str[i], &start, &last) == 0)
			printf("minishell: export: `%s': not a valid identifier\n", str[i]);
		i++;
	}
	env = start;
}


void	export_f(utils_t *utils, char **str)
{
	t_duplicate_env	*start;
	int				i;

	i = 0;
	start = utils->shell->duplicate_env;
	if (str[1])
		input_export(utils->shell->duplicate_env ,&str[1]);
	else if (str[0] && !str[1])
	{
		add_enviorment(utils->shell);
		ft_env_elem_sort(&utils->shell->input_export , ft_strcmp);
		print_export_list(utils);
	}
}
