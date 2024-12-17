/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:04:03 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/09 13:00:31 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

void	block_arr_cleaner(t_block *p_block)
{
	while (p_block)
	{
		if (p_block->type == SUBSH)
			block_arr_cleaner(p_block->subsh_block_arr);
		else
			clean_argv_memory(p_block->exec_argv);
		if (p_block->next)
		{
			p_block = p_block->next;
			free(p_block->prev);
		}
		else
		{
			free(p_block);
			p_block = 0;
		}
	}
}

void	utils_reset(t_utils *utils)
{
	utils->in_block = 0;
	if (utils->i_string != 0)
		free(utils->i_string);
	utils->i_string = 0;
	utils->hd_eof = 0;
	utils->hd_mode = 0;
	utils->hd_stop = 0;
	utils->parsh_block = 0;
	utils->ok_to_cnt = 1;
	utils->reading = 0;
	utils->parsh_block = 0;
}

void	clean_all_fd(t_block *block)
{
	block = last_block(block);
	while (block)
	{
		if (block->input_fd != 0)
			close(block->input_fd);
		if (block->output_fd != 1)
			close(block->output_fd);
		if (block->tmp_pipe_input_fd != 0)
			close(block->tmp_pipe_input_fd);
		block = block->prev;
	}
}

void	clean_some_staff_after_export(t_utils *utils)
{
	t_export	*input_export;
	t_export	*temp;

	input_export = utils->shell->input_export;
	while (input_export)
	{
		free(input_export->key);
		free(input_export->value);
		temp = input_export;
		input_export = input_export->next;
		free(temp);
	}
	utils->shell->input_export = 0;
}

//This function cleans token's structure after the line execution

void	cleaner(t_block **block_arr, t_utils *utils)
{
	DIR				*dir;
	struct dirent	*entry;

	block_arr_cleaner(*block_arr);
	*block_arr = 0;
	utils_reset(utils);
	dir = opendir(".");
	if (dir == 0)
		return ;
	entry = readdir(dir);
	clean_some_staff_after_export(utils);
	while (entry != 0)
	{
		if (ft_strncmp("minishel_temp_file", entry->d_name, 18) == 0)
			unlink(entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	return ;
}
