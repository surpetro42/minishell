/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:26:22 by surpetro          #+#    #+#             */
/*   Updated: 2024/11/21 19:44:04 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishel.h"

void free_dollar(t_var_dollar var)
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
}
