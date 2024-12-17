/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_doc_processor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:50:32 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/15 12:09:31 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

/*****h_doc_processor*****/
int	hd_temp_file_creator(char *filename)
{
	int	i;
	int	fd;

	ft_strlcpy(filename, "minishel_temp_file", 35);
	i = 0;
	filename_creator(filename, i);
	while (access(filename, F_OK) == 0 && i <= 16)
		filename_creator(filename, ++i);
	if (i > 16)
		return (printf("bash: maximum here-document count exceeded\n"), 1);
	fd = open(filename, O_RDWR | O_CREAT | O_EXCL, 0644);
	if (fd == -1)
		return (my_perror("minishell", filename), fd);
	return (fd);
}

int	hd_mode_finder(char *str, int i)
{
	while (str[i] && is_not_special(str[i]))
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	hd_eof_extractor(t_utils *utils, int *index)
{
	int		size;
	char	*ch;

	*index += 2;
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
	size = count_phrase_size(utils->i_string, *index);
	utils->hd_mode = hd_mode_finder(utils->i_string, *index);
	utils->hd_eof = (char *)malloc(size + 5);
	if (utils->hd_eof == 0)
		return (perror("hd EOF malloc"), 1);
	extract_the_phrase(utils->hd_eof, utils->i_string, index);
	restore_hidden_dollar(utils->hd_eof);
	return (0);
}

int	write_to_file(int fd, t_utils *utils)
{
	char	*i_str;
	char	*tmp;

	while (1)
	{
		i_str = hd_getstring(utils);
		if (i_str == 0)
			return (0);
		if (utils->hd_stop == 1)
			return (1);
		if (ft_strcmp(i_str, utils->hd_eof) == 0)
			break ;
		if (utils->hd_mode == 0)
		{
			tmp = dollar_func(i_str, utils);
			free(i_str);
			i_str = tmp;
		}
		write(fd, i_str, ft_strlen(i_str));
		write(fd, "\n", 1);
		free (i_str);
	}
	return (free(i_str), 0);
}

int	h_doc_processor(int *index, t_block **p_block_arr, t_utils *utils)
{
	t_block	*p_block;
	char	filename[35];

	if (utils->in_block == 0)
		if (next_block_creator(p_block_arr, utils) == 1)
			return (1);
	p_block = last_block(*p_block_arr);
	p_block->input_fd = hd_temp_file_creator(filename);
	if (p_block->input_fd == -1)
		return (1);
	if (hd_eof_extractor(utils, index) == 1)
		return (1);
	if (write_to_file(p_block->input_fd, utils) == 1)
		return (free(utils->hd_eof), 1);
	close(p_block->input_fd);
	p_block->input_fd = open(filename, O_RDONLY);
	return (free(utils->hd_eof), 0);
}
