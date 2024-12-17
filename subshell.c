/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:04:04 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/07 19:05:13 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

/***regular_subshell***/
void	close_subshell_fds(t_block *block, t_utils *utils)
{
	while (block != 0)
	{
		if (block->input_fd != 0)
			close(block->input_fd);
		if (block->output_fd != 1)
			close(block->output_fd);
		if (block->type == EXEC)
			block = block->next;
		else
		{
			close_subshell_fds(block->subsh_block_arr, utils);
			block = block->next;
		}
	}
}

int	subsh_waiting_or_no(int pid, t_block *block, t_utils *utils)
{
	int	temp;

	close_subshell_fds(block->subsh_block_arr, utils);
	if (block->next_logic_elem != MY_PIPE)
	{
		if (waitpid(pid, &(block->exit_status), 0) != pid)
			return (my_perror("minishell", ""), 0);
		utils->last_exit_status = block->exit_status;
		exit_status_processing(block, utils);
		while (wait(&temp) != -1)
			;
	}
	else
	{
		block->exit_status = 0;
		utils->last_exit_status = 0;
		utils->ok_to_cnt = 1;
	}
	return (0);
}

void	regular_subshell_child(t_block *block, t_utils *utils)
{
	if (dup2(block->input_fd, 0) == -1 || dup2(block->output_fd, 1) == -1)
	{
		my_perror("minishell", "subhsell");
		full_clean(block, utils);
		exit(1);
	}
	if (block->input_fd != 0)
		close(block->input_fd);
	if (block->output_fd != 1)
		close(block->output_fd);
	executor(block->subsh_block_arr, utils);
	full_clean(block, utils);
	exit (utils->last_exit_status);
}

int	regular_subshell(t_block *block, t_utils *utils)
{
	int	pid;

	if (block->input_fd == -1 || block->output_fd == -1)
	{
		if (block->input_fd > 0)
			close(block->input_fd);
		if (block->output_fd > 1)
			close(block->output_fd);
		utils->last_exit_status = 1;
		return (0);
	}
	pid = fork();
	if (pid == -1)
		return (my_perror("minishell: ", "subshell"), 1);
	else if (pid == 0)
		regular_subshell_child(block, utils);
	if (block->input_fd != 0)
		close(block->input_fd);
	if (block->output_fd != 1)
		close(block->output_fd);
	return (subsh_waiting_or_no(pid, block, utils));
}
