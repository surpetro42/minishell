/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:08:23 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/07 19:11:26 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

/***********************EXECUTOR****************************/

/***pipe_exec***/

int	pipes_creator(t_block *block)
{
	int	fd[2];
	int	i;

	i = 0;
	while (block->next_logic_elem == MY_PIPE)
	{
		if (pipe(fd) == -1)
			return (my_perror("minishell", "pipes_creator"), 1);
		if (block->output_fd == 1)
			block->output_fd = fd[1];
		else
			close(fd[1]);
		if (block->next->input_fd == 0)
			block->next->input_fd = fd[0];
		else
			block->next->tmp_pipe_input_fd = fd[0];
		block = block->next;
		i++;
		if (i > 100)
			return (write(2, \
			"minishell: fork: Resource temporarily unavailable\n", 50), 1);
	}
	return (0);
}

int	pipe_exec(t_block **p_block, t_utils *utils)
{
	t_block	*block;

	block = *p_block;
	if (pipes_creator(block) == 1)
		return (1);
	while (block != 0)
	{
		if (block->type == EXEC)
			regular_exec(block, utils);
		else if (block->type == SUBSH)
			if (regular_subshell(block, utils) == 1)
				return (1);
		if (block->tmp_pipe_input_fd != 0)
			close (block->tmp_pipe_input_fd);
		if (block->next_logic_elem != MY_PIPE)
			break ;
		block = block->next;
	}
	*p_block = block;
	return (0);
}

void	clean_block_fd(t_block *block)
{
	if (block->input_fd != 0)
		close(block->input_fd);
	if (block->output_fd != 1)
		close(block->output_fd);
}

int	executor(t_block *block, t_utils *utils)
{
	int	ret_val;

	ret_val = 0;
	while (block != 0 && utils->ok_to_cnt && ret_val == 0)
	{
		if (block->type == EXEC && block->next_logic_elem != MY_PIPE)
			ret_val = regular_exec(block, utils);
		else if (block->type == SUBSH && block->next_logic_elem != MY_PIPE)
			ret_val = regular_subshell(block, utils);
		else if (block->next_logic_elem == MY_PIPE)
			ret_val = pipe_exec(&block, utils);
		else
			clean_block_fd(block);
		if (ret_val == 0)
			block = block->next;
	}
	if (ret_val != 0)
		clean_all_fd(block);
	return (ret_val);
}
