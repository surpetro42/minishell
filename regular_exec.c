/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regular_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 19:00:32 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/15 12:20:17 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

void	close_next_blocks_fd(t_block *block)
{
	block = block->next;
	while (block)
	{
		if (block->input_fd != 0)
			close(block->input_fd);
		if (block->output_fd != 1)
			close(block->output_fd);
		block = block->next;
	}
}

int	reg_exec_child(t_block *block, t_utils *utils, char *exec)
{
	signal(SIGQUIT, SIG_DFL);
	close_next_blocks_fd(block);
	if (dup2(block->input_fd, 0) == -1 || dup2(block->output_fd, 1) == -1)
		return (my_perror("minishell", exec), free(exec), \
			full_clean(block, utils), 1);
	if (block->input_fd != 0)
		close(block->input_fd);
	if (block->output_fd != 1)
		close(block->output_fd);
	if (is_builtin(exec))
	{
		if (ft_strcmp(exec, "exit") == 0)
			close(block->output_fd);
		return (run_builtin(block, utils));
	}
	execve(exec, block->exec_argv, utils->env);
	my_perror("minishell", exec);
	return (free(exec), full_clean(block, utils), 1);
}

int	waiting_or_no(int pid, char *exec, t_block *block, t_utils *utils)
{
	int	temp;

	if (block->next_logic_elem != MY_PIPE)
	{
		if (waitpid(pid, &(block->exit_status), 0) != pid)
		{
			utils->last_exit_status = 1;
			return (my_perror("minishell: ", exec), free(exec), 0);
		}
		block->exit_status = status_decoder(block->exit_status);
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
	free (exec);
	return (0);
}

int	regular_exec_initial_checks(t_block *block, t_utils *utils)
{
	if (block->input_fd == -1 || block->output_fd == -1)
	{
		if (block->input_fd > 0)
			close(block->input_fd);
		if (block->output_fd > 1)
			close(block->output_fd);
		utils->last_exit_status = 1;
		return (0);
	}
	if (is_builtin(block->exec_argv[0]) && block->next_logic_elem != MY_PIPE \
		&& ((block->prev && block->prev->next_logic_elem != MY_PIPE) \
			|| block->prev == 0))
	{
		regular_exec_initial_checks_2(block, utils);
		return (0);
	}
	return (1);
}

int	regular_exec(t_block *block, t_utils *utils)
{
	char			*exec;
	int				pid;
	int				ret_val;

	ret_val = regular_exec_initial_checks(block, utils);
	if (ret_val == 0)
		return (close_block_fd(block), 0);
	exec = exec_compose(block->exec_argv[0], utils);
	if (exec == 0)
		return (exit_status_processing(block, utils), close_block_fd(block), 0);
	pid = fork();
	if (pid == -1)
		return (my_perror("minishell", exec), 1);
	else if (pid == 0)
		exit (reg_exec_child(block, utils, exec));
	close_block_fd(block);
	return (waiting_or_no(pid, exec, block, utils));
}
