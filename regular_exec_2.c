/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regular_exec_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:12:32 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/15 13:12:49 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

void	close_block_fd(t_block *block)
{
	if (block->input_fd != 0)
		close(block->input_fd);
	if (block->output_fd != 1)
		close(block->output_fd);
}

void	regular_exec_initial_checks_2(t_block *block, t_utils *utils)
{
	int	fd[2];

	if (builtin_fd_chng(fd, block) == 1)
	{
		utils->last_exit_status = 1;
		return ;
	}
	run_builtin(block, utils);
	if (builtin_fd_revert(fd) == 1)
		utils->last_exit_status = 1;
}

void	exit_status_processing(t_block *block, t_utils *utils)
{
	if ((utils->last_exit_status == 0 && block->next_logic_elem == AND_AND) || \
		(utils->last_exit_status != 0 && block->next_logic_elem == OR_OR) || \
		block->next_logic_elem == MY_PIPE)
		utils->ok_to_cnt = 1;
	else
		utils->ok_to_cnt = 0;
}
