/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:44:06 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/07 14:45:34 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

/************************BLOCK MANIPULATION***************************/

void	block_init(t_block *block)
{
	block->type = 0;
	block->input_fd = 0;
	block->output_fd = 1;
	block->tmp_pipe_input_fd = 0;
	block->next_logic_elem = 0;
	block->exit_status = 0;
	block->exec_argv = 0;
	block->subsh_block_arr = 0;
	block->parsh_block = 0;
	block->next = 0;
	block->prev = 0;
	block->index = 0;
}

t_block	*last_block(t_block *block_arr)
{
	t_block	*ret_ptr;

	ret_ptr = block_arr;
	if (block_arr == 0)
	{
		write(2, "minishell: last_block function argument is NULL\n", 48);
		return (0);
	}
	while (ret_ptr->next != 0)
		ret_ptr = ret_ptr->next;
	return (ret_ptr);
}

int	next_block_creator(t_block **p_block_arr, t_utils *utils)
{
	t_block	*new_block;
	t_block	*l_block;

	new_block = (t_block *)malloc(sizeof(t_block));
	if (new_block == 0)
		return (perror("block creation"), 1);
	block_init(new_block);
	utils->in_block = 1;
	if (*p_block_arr == 0)
	{
		*p_block_arr = new_block;
		return (0);
	}
	l_block = last_block(*p_block_arr);
	l_block->next = new_block;
	new_block->prev = l_block;
	new_block->index = l_block->index + 1;
	return (0);
}
