/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:09:48 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/15 12:22:07 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int	sub_tokenizer(t_block **p_block_arr, t_utils *utils, int *i, int ret_val)
{
	if (utils->i_string[*i] == ' ')
		space_processor(i, utils->i_string);
	else if (utils->i_string[*i] == '<' && utils->i_string[*i + 1] == '<' )
		ret_val = h_doc_processor(i, p_block_arr, utils);
	else if (utils->i_string[*i] == '<')
		ret_val = s_input_processor(i, p_block_arr, utils);
	else if (utils->i_string[*i] == '>' && utils->i_string[*i + 1] == '>' )
		ret_val = s_output_processor(i, p_block_arr, utils, 0);
	else if (utils->i_string[*i] == '>')
		ret_val = s_output_processor(i, p_block_arr, utils, 1);
	else if (utils->i_string[*i] == '&' && utils->i_string[*i + 1] == '&')
		ret_val = logical_and_processor(i, p_block_arr, utils);
	else if (utils->i_string[*i] == '|' && utils->i_string[*i + 1] == '|')
		ret_val = logical_or_processor(i, p_block_arr, utils);
	else if (utils->i_string[*i] == '|')
		ret_val = pipe_processor(i, p_block_arr, utils);
	else if (utils->i_string[*i] != '(' && utils ->i_string[*i] != ')')
		ret_val = command_processor(i, p_block_arr, utils);
	return (ret_val);
}

int	tokenizer(t_block **p_block_arr, t_utils *utils)
{
	int	i;
	int	ret_val;

	i = 0;
	ret_val = 0;
	while (utils->i_string[i] && ret_val == 0)
	{
		ret_val = sub_tokenizer(p_block_arr, utils, &i, ret_val);
		if (utils->i_string[i] == '(')
			ret_val = parenthesis_open(&i, &p_block_arr, utils);
		else if (utils->i_string[i] == ')')
			ret_val = parenthesis_close(&i, &p_block_arr, utils);
	}
	utils->last_exit_status = ret_val;
	if (ret_val != 0)
		clean_all_fd(*p_block_arr);
	return (ret_val);
}
