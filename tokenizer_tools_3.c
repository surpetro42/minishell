/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_tools_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:04:58 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/07 15:09:37 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

/*****logical_and_processor*****/
int	logical_and_processor(int *index, t_block **p_block_arr, t_utils *utils)
{
	t_block	*p_block;

	if (utils->in_block == 0)
		return (write(2, "minishell: Syntax error near unexpected token &&\n", \
					49), 1);
	p_block = last_block(*p_block_arr);
	p_block->next_logic_elem = AND_AND;
	utils->in_block = 0;
	*index += 2;
	space_processor(index, utils->i_string);
	return (0);
}

/*****logical_or_processor*****/
int	logical_or_processor(int *index, t_block **p_block_arr, t_utils *utils)
{
	t_block	*p_block;

	if (utils->in_block == 0)
		return (write(2, "minishell: Syntax error near unexpected token ||\n", \
					49), 1);
	p_block = last_block(*p_block_arr);
	p_block->next_logic_elem = OR_OR;
	utils->in_block = 0;
	*index += 2;
	space_processor(index, utils->i_string);
	return (0);
}

/*******pipe_processor*******/
int	pipe_processor(int *index, t_block **p_block_arr, t_utils *utils)
{
	t_block	*p_block;

	if (utils->in_block == 0)
		return (write(2, "minishell: Syntax error near unexpected token |\n", \
					48), 1);
	p_block = last_block(*p_block_arr);
	p_block->next_logic_elem = MY_PIPE;
	utils->in_block = 0;
	*index += 1;
	space_processor(index, utils->i_string);
	if (utils->i_string[*index] == 0)
		return (write(2, \
		"minishell: Syntax error near unexpected token newline\n", 54), 1);
	return (0);
}

/*******parenthesis_open*******/
int	parenthesis_open(int *index, t_block ***p_p_block_arr, t_utils *utils)
{
	t_block	*p_block;

	if (utils->in_block == 1)
		return (write(2, "minishell: Syntax error near unexpected token (\n", \
					49), 1);
	if (next_block_creator(*p_p_block_arr, utils) == 1)
		return (1);
	p_block = last_block(**p_p_block_arr);
	p_block->parsh_block = utils->parsh_block;
	p_block->type = SUBSH;
	p_block->exec_argv = (void *)1;
	utils->parsh_block = *p_p_block_arr;
	*p_p_block_arr = &(p_block->subsh_block_arr);
	utils->in_block = 0;
	(*index)++;
	space_processor(index, utils->i_string);
	return (0);
}

/*******parenthesis_close*******/
int	parenthesis_close(int *index, t_block ***p_p_block_arr, t_utils *utils)
{
	t_block	*p_block;

	*p_p_block_arr = utils->parsh_block;
	p_block = last_block(**p_p_block_arr);
	utils->parsh_block = p_block->parsh_block;
	(*index)++;
	space_processor(index, utils->i_string);
	utils->in_block = 1;
	return (0);
}
