/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 23:06:17 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/09 23:06:55 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishel.h"

void	final_block_arr_cleaner(t_block *block)
{
	while (block)
	{
		if (block->input_fd != 0)
			close(block->input_fd);
		if (block->output_fd != 1)
			close(block->output_fd);
		if (block->tmp_pipe_input_fd != 0)
			close(block->tmp_pipe_input_fd);
		if (block->type == SUBSH)
			block_arr_cleaner(block->subsh_block_arr);
		else
			clean_argv_memory(block->exec_argv);
		if (block->prev)
		{
			block = block->prev;
			free(block->next);
		}
		else
		{
			free(block);
			block = 0;
		}
	}
}
