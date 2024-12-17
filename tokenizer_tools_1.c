/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:53:39 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/07 15:14:49 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

void	space_processor(int *index, char *str)
{
	while (str[*index] && str[*index] == ' ')
		(*index)++;
}

/*****s_input_processor*****/
int	s_input_processor2(int *index, t_block *p_block, t_utils *utils)
{
	char	filename[260];
	char	*new_filename;
	int		size;

	if (p_block->input_fd == -1 || p_block->output_fd == -1)
		return (0);
	size = count_phrase_size(utils->i_string, *index);
	if (size > 256)
		return (perror("minishell: File name too long"), 1);
	extract_the_phrase(filename, utils->i_string, index);
	space_processor(index, utils->i_string);
	new_filename = dollar_func(filename, utils);
	restore_hidden_dollar(new_filename);
	p_block->input_fd = open(new_filename, O_RDONLY);
	if (p_block->input_fd == -1)
		return (my_perror("minishel", new_filename), free(new_filename), 0);
	free (new_filename);
	return (0);
}

int	s_input_processor(int *index, t_block **p_block_arr, t_utils *utils)
{
	t_block	*p_block;
	char	*ch;

	if (utils->in_block == 0)
		if (next_block_creator(p_block_arr, utils) == 1)
			return (1);
	p_block = last_block(*p_block_arr);
	(*index)++;
	space_processor(index, utils->i_string);
	if (is_not_special(utils->i_string[*index]) == 0)
	{
		ch = &(utils->i_string[*index]);
		if ((*ch == '<' && *(ch + 1) == '<') || (*ch == '>' && *(ch + 1) == \
'>') || (*ch == '&' && *(ch + 1) == '&') || (*ch == '|' && *(ch + 1) == '|'))
			return (write(2, "minishell: syntax error near unexpected token '"\
						, 47), write(2, ch, 2), write(2, "'\n", 2), 1);
		return (write(2, "minishell: syntax error near unexpected token '", \
						47), write(2, ch, 1), write(2, "'\n", 2), 1);
	}
	return (s_input_processor2(index, p_block, utils));
}

/*****s_output_processor*****/
int	s_output_processor2(int *index, t_block *p_block, t_utils *utils, int mode)
{
	char	filename[260];
	char	*new_filename;
	int		size;

	if (p_block->output_fd == -1 || p_block->input_fd == -1)
		return (0);
	size = count_phrase_size(utils->i_string, *index);
	if (size > 256)
		return (perror("minishell: File name too long"), 1);
	extract_the_phrase(filename, utils->i_string, index);
	new_filename = dollar_func(filename, utils);
	restore_hidden_dollar(new_filename);
	if (mode == 1)
		p_block->output_fd = open(new_filename, O_WRONLY | O_TRUNC | O_CREAT, \
				0644);
	else
		p_block->output_fd = open(new_filename, O_WRONLY | O_APPEND | O_CREAT, \
				0644);
	if (p_block->output_fd == -1)
		return (my_perror("minishell", new_filename), free(new_filename), 0);
	free(new_filename);
	return (0);
}

int	s_output_processor(int *index, t_block **p_block_arr, t_utils *utils, \
		int mode)
{
	t_block	*p_block;
	char	*ch;

	if (utils->in_block == 0)
		if (next_block_creator(p_block_arr, utils) == 1)
			return (1);
	p_block = last_block(*p_block_arr);
	if (mode == 1)
		(*index)++;
	else
		(*index) += 2;
	space_processor(index, utils->i_string);
	if (is_not_special(utils->i_string[*index]) == 0)
	{
		ch = &(utils->i_string[*index]);
		if ((*ch == '<' && *(ch + 1) == '<') || (*ch == '>' && *(ch + 1) == \
'>') || (*ch == '&' && *(ch + 1) == '&') || (*ch == '|' && *(ch + 1) == '|'))
			return (write(2, "minishell: syntax error near unexpected token '"\
						, 47), write(2, ch, 2), write(2, "'\n", 2), 1);
		return (write(2, "minishell: syntax error near unexpected token '", \
						47), write(2, ch, 1), write(2, "'\n", 2), 1);
	}
	return (s_output_processor2(index, p_block, utils, mode));
}
