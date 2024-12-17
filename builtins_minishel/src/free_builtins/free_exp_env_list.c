/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exp_env_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:26:22 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/09 19:55:24 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishel.h"

void	free_env_list(t_duplicate_env *list)
{
	t_duplicate_env	*tmp;

	while (list)
	{
		tmp = list;
		if (list->key)
			free(list->key);
		if (list->value)
			free(list->value);
		list = list->next;
		free(tmp);
	}
}

void	free_exp_list(t_export *list)
{
	t_export	*tmp;

	while (list)
	{
		tmp = list;
		if (list->key)
			free(list->key);
		if (list->value)
			free(list->value);
		list = list->next;
		free(tmp);
	}
}
