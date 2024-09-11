/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:03:36 by surpetro          #+#    #+#             */
/*   Updated: 2024/08/06 19:42:56 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)env;

	if (argc > 1)
		return 1;
	t_shell	*shell;
	int i;

	shell = malloc(sizeof(t_shell));
	shell->arguments = NULL;
	i = 0;
	while (1)
	{
		shell->input = readline("\033[38;5;43mminishell: \033[0;000m");
		ctrl_d(shell);
		tokenization(shell);
	}
	return 0;
}
