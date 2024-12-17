/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 18:55:07 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/08 14:52:09 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int	is_builtin(char *exec)
{
	if (ft_strcmp(exec, "echo") == 0)
		return (1);
	else if (ft_strcmp(exec, "pwd") == 0)
		return (2);
	else if (ft_strcmp(exec, "cd") == 0)
		return (3);
	else if (ft_strcmp(exec, "export") == 0)
		return (4);
	else if (ft_strcmp(exec, "unset") == 0)
		return (5);
	else if (ft_strcmp(exec, "env") == 0)
		return (6);
	else if (ft_strcmp(exec, "exit") == 0)
		return (7);
	else
		return (0);
}

int	builtin_fd_chng(int *fd, t_block *block)
{
	int	temp[2];

	fd[0] = dup(0);
	fd[1] = dup(1);
	if (fd[0] == -1 || fd[1] == -1)
		return (my_perror("minishell", "fd_change_for_builtin"), 1);
	temp[0] = dup2(block->input_fd, 0);
	temp[1] = dup2(block->output_fd, 1);
	if (temp[0] == -1 || temp[1] == -1)
		return (my_perror("minishell", "fd_change_for_builtin"), 1);
	if (block->input_fd != 0)
		close(block->input_fd);
	if (block->output_fd != 1)
		close(block->output_fd);
	return (0);
}

int	builtin_fd_revert(int *fd)
{
	int	temp[2];

	if (fd[0] != -1)
	{
		close(0);
		temp[0] = dup2(fd[0], 0);
		close(fd[0]);
	}
	if (fd[1] != -1)
	{
		close(1);
		temp[1] = dup2(fd[1], 1);
		close(fd[1]);
	}
	if (temp[0] == -1 || temp[1] == -1)
		return (my_perror("minishell: ", "fd_revert_builtins"), 1);
	return (0);
}

int	run_builtin(t_block *block, t_utils *utils)
{
	int	type;

	block->exit_status = 0;
	type = is_builtin(block->exec_argv[0]);
	if (type == 1)
		echo(block->exec_argv, utils);
	else if (type == 3)
		block->exit_status = cd(block->exec_argv[1], utils);
	else if (type == 6)
		env_print(utils);
	else if (type == 4)
		block->exit_status = export_f(utils, block->exec_argv);
	else if (type == 5)
		block->exit_status = unset_f(utils, block->exec_argv);
	else if (type == 2)
		pwd(utils);
	else if (type == 7)
		block->exit_status = my_exit(block, utils);
	utils->last_exit_status = block->exit_status;
	exit_status_processing(block, utils);
	return (block->exit_status);
}
