/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_tools_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:01:45 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/15 12:23:52 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

/*****command_processor*****/
int	command_processor_error(int *index, t_utils *utils)
{
	char	*temp;
	int		size;

	size = count_phrase_size(utils->i_string, *index);
	temp = (char *)malloc(sizeof(char) * (size +5));
	if (temp == 0)
		return (my_perror("minishell", "command processor error message"), 1);
	extract_the_phrase_2(temp, utils->i_string, index);
	write(2, "minishell: Syntax error near unexpected token '", 47);
	write(2, temp, ft_strlen(temp));
	write(2, "'\n", 2);
	free (temp);
	return (0);
}

int	sub_command_processor2(int *index, t_block *p_block, t_utils *utils, int i)
{
	int		size;
	char	*temp;

	while (utils->i_string[*index] && is_not_special(utils->i_string[*index]))
	{
		size = count_phrase_size(utils->i_string, *index);
		temp = (char *)malloc(sizeof(char) * (size + 15));
		if (temp == 0)
			return (my_perror("minishell", "command_processor"), 1);
		extract_the_phrase_2(temp, utils->i_string, index);
		p_block->exec_argv[i] = dollar_func(temp, utils);
		restore_hidden_dollar(p_block->exec_argv[i]);
		if (temp[0] == '$' && i == 0 && ft_strcmp(p_block->exec_argv[0], \
					"") == 0)
		{
			free(p_block->exec_argv[0]);
			p_block->exec_argv[0] = 0;
			i--;
		}
		i++;
		free(temp);
		space_processor(index, utils->i_string);
	}
	return (0);
}

int	command_processor2(int *index, t_block *p_block, t_utils *utils)
{
	int		i;

	i = 0;
	while (p_block->exec_argv[i] != 0)
		i++;
	if (sub_command_processor2(index, p_block, utils, i) == 1)
		return (1);
	if (p_block->exec_argv[0] == 0)
		p_block->exec_argv[0] = ft_calloc(1, sizeof(char));
	return (argv_wildcard_processor(p_block));
}

int	new_exec_argv_creator(char ***exec_argv, int new_size)
{
	int		old_size;
	char	**temp;
	int		i;

	old_size = 0;
	while ((*exec_argv)[old_size] != 0)
		old_size++;
	temp = (char **)ft_calloc(old_size + new_size + 5, sizeof(char *));
	if (temp == 0)
		return (my_perror("minishell", " command_processor"), 1);
	i = 0;
	while (i < old_size)
	{
		temp[i] = (char *)malloc(sizeof(char) * (ft_strlen((*exec_argv)[i]) \
					+ 5));
		ft_strlcpy(temp[i], (*exec_argv)[i], ft_strlen((*exec_argv)[i]) + 5);
		i++;
	}
	i = 0;
	while ((*exec_argv)[i])
		free((*exec_argv)[i++]);
	free(*exec_argv);
	*exec_argv = temp;
	return (0);
}

int	command_processor(int *index, t_block **p_block_arr, t_utils *utils)
{
	t_block	*p_block;
	int		size;

	if (is_not_special(utils->i_string[*index]) == 0)
		return (write(2, "minishell: syntax error near unexpected token '", \
		47), write(2, &(utils->i_string[*index]), 1), write(2, "'\n", 2), 1);
	if (utils->in_block == 0)
		if (next_block_creator(p_block_arr, utils) == 1)
			return (1);
	p_block = last_block(*p_block_arr);
	if (p_block->exec_argv == (char **)1)
		return (command_processor_error(index, utils), 1);
	size = count_words(utils->i_string, *index);
	if (p_block->exec_argv != 0)
	{
		if (new_exec_argv_creator(&(p_block->exec_argv), size) == 1)
			return (1);
	}
	else
		p_block->exec_argv = (char **)ft_calloc(size + 5, sizeof(char *));
	if (p_block->exec_argv == 0)
		return (my_perror("minishell", "command_processor"), 1);
	p_block->type = EXEC;
	return (command_processor2(index, p_block, utils));
}
