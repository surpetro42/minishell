/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:00:30 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/15 12:07:42 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishel.h"

void	aram_cleanup(t_block *block, t_utils *utils)
{
	if (block != 0)
	{
		block = last_block(block);
		final_block_arr_cleaner(block);
	}
	if (utils->i_string != 0)
		free(utils->i_string);
}

void	suren_cleanup(t_utils *utils)
{
	(void)utils;
	free_env_list(utils->shell->duplicate_env);
	free_exp_list(utils->shell->input_export);
}

void	full_clean(t_block *block, t_utils *utils)
{
	suren_cleanup(utils);
	aram_cleanup(block, utils);
}

int	exit_status_extractor(char *str, int i, int sign, int exit_status)
{
	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[0] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		exit_status *= 10;
		exit_status += str[i] - '0';
		i++;
	}
	if (str[i] != 0)
	{
		write(2, "minishell: exit: ", 17);
		write(2, str, ft_strlen(str));
		write(2, ": numeric argument required\n", 28);
		exit_status = 300;
	}
	else
		exit_status *= sign;
	return (exit_status);
}

int	my_exit(t_block *block, t_utils *utils)
{
	int	exit_status;

	exit_status = 0;
	write(1, "exit\n", 5);
	if (block->exec_argv[1] != 0)
		exit_status = exit_status_extractor(block->exec_argv[1], 0, 1, 0);
	else
		exit_status = utils->last_exit_status;
	if (exit_status != 300 && block->exec_argv[1] != 0 && block->exec_argv[2] \
			!= 0)
	{
		write (2, "minishell: exit: too many arguments\n", 36);
		utils->last_exit_status = 1;
		return (1);
	}
	full_clean(block, utils);
	if (exit_status == 300)
		exit_status = 255;
	exit(exit_status);
}
