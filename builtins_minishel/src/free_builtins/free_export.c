/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:26:22 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/10 18:31:54 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishel.h"

void	free_export(t_var_export var)
{
	if (var.buff_key)
		free(var.buff_key);
	if (var.buff_vlaue)
		free(var.buff_vlaue);
}
