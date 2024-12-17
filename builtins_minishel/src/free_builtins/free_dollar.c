/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:26:22 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/09 19:54:58 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishel.h"

void	free_dollar(t_var_dollar var)
{
	if (var.s1_before)
		free(var.s1_before);
	if (var.s2_key)
		free(var.s2_key);
	if (var.s3_after)
		free(var.s3_after);
	if (var.res_1)
		free(var.res_1);
	if (var.res_line_key)
		free(var.res_line_key);
	if (var.buff)
		free(var.buff);
	if (var.res_line)
		free(var.res_line);
	if (var.res_line_remains)
		free(var.res_line_remains);
	if (var.res_buff)
		free(var.res_buff);
	if (var.line)
		free(var.line);
	if (var.open_exit_status)
		free(var.open_exit_status);
}
