/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:00:30 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/04 22:34:51 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishel.h"

void	aram_cleanup(block_t *block, utils_t *utils)
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
		free(utils->i_string);
	}
}

void	suren_cleanup(utils_t *utils)
{
	(void)utils;
	// free_env_list(utils->shell->duplicate_env);
	// free_exp_list(utils->shell->input_export);
}

void	full_clean(block_t *block, utils_t *utils)
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
			exit_status = 255;
		}
		else
			exit_status *= sign;
		return (exit_status);
}

void	my_exit(block_t *block, utils_t *utils)
{
	int		exit_status;

	write(1, "exit\n", 5);
	if (block->exec_argv[1] != 0 && block->exec_argv[2] == 0)
		exit_status = exit_status_extractor(block->exec_argv[1], 0, 1, 0);
	else if (block->exec_argv[1] != 0 && block->exec_argv[2] != 0)
	{
		write (2, "too many arguments\n", 19);
		exit_status = 1;
	}
	else
		exit_status = utils->last_exit_status;
	full_clean(block, utils);
	// system("leaks minishell");
	exit(exit_status);
}
