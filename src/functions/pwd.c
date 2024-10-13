/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 21:58:24 by surpetro          #+#    #+#             */
/*   Updated: 2024/10/07 18:05:32 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(utils_t *utils)
{
	(void)utils;
	char	cwd[PASS_MAX];
	if (getcwd(cwd, PASS_MAX) != NULL)
		printf("%s\n", cwd);
}
