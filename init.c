/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:51:41 by ayeganya          #+#    #+#             */
/*   Updated: 2024/11/12 18:11:59 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

//This function cleans token's structure after the line execution

void	block_arr_cleaner(block_t *p_block)
{
	while (p_block)
	{
		if (p_block->type == SUBSH)
			block_arr_cleaner(p_block->subsh_block_arr);
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

void	utils_reset(utils_t *utils)
{
	//utils->env = env;
	utils->new_word = 1;
	utils->in_block = 0;
	utils->i_string = 0;
	utils->hd_eof = 0;
	utils->hd_mode = 0;
	utils->i_string = 0;
	utils->parsh_block = 0;
	utils->ok_to_cnt = 1;
	//utils->last_exit_status = 0;
}

void	cleaner(block_t **block_arr, utils_t *utils)
{
	block_arr_cleaner(*block_arr);
	*block_arr = 0;
	utils_reset(utils);
	return ;
}

//This function should be called before exit to clean up all resources
void	full_clean(block_t *block_arr, utils_t *utils)
{
	(void)utils;
	(void)block_arr;
	return ;
}

//Function placeholders
void	my_exit(block_t *block_arr, utils_t *utils)
{
	(void)block_arr;
	(void)utils;
	exit(0);
}

int	var_substitute(block_t *block_arr, utils_t *utils)
{
	(void)block_arr;
	(void)utils;
	return (0);
}
/*
void	executor(block_t *block_arr, utils_t *utils)
{
	(void)block_arr;
	(void)utils;
	return ;
}*/

void	get_string(utils_t *utils)
{
	utils->i_string = readline(PROMPT);
	if (utils->i_string == 0)
	{
		full_clean(0, utils);
		exit (0);
	}
	add_history(utils->i_string);
}

/************SYNTAX_CHECK************/

int	find_the_pair_quote(char *i_string, int *index)
{
	char quote;
	int i;

	i = *index;
	quote = i_string[i];
	i++;
	while(i_string[i] && i_string[i] != quote)
		i++;
	*index = i;
	if (i_string[i] == 0)
		return (1);
	else
		return (0);
}

int	quotes_checker(utils_t *utils)
{
	int	i;
	int	pair;

	i = 0;
	while (utils->i_string[i])
	{
		if (utils->i_string[i] == '"' || utils->i_string[i] == '\'')
			pair = find_the_pair_quote(utils->i_string, &i);
		if (pair == 1)
		{
			printf(QTS_ERROR);
			return (1);
		}
		i++;
	}
	return (0);
}

int	parenthesis_checker(utils_t *utils)
{
	int	i;
	int p_count;

	i = 0;
	p_count = 0;
	while (p_count >=0 && utils->i_string[i])
	{
		if (utils->i_string[i] == '"' || utils->i_string[i] == '\'')
			find_the_pair_quote(utils->i_string, &i);
		if (utils->i_string[i] == '(')
			p_count++;
		else if (utils->i_string[i] == ')')
			p_count--;
		i++;
	}
	if (p_count != 0)
	{
		printf(PRNTHS_ERROR);
		return (1);
	}
	return (0);
}

int	syntax_check(utils_t *utils)
{
	if (quotes_checker(utils) == 1 || parenthesis_checker(utils) == 1)
		return (1);
	return (0);
}

/****************************TOOLS************************************/
void	my_perror(char *prefix, char *suffix)
{
	char *error_message;

	error_message = strerror(errno);
	if (prefix)
		write(2, prefix, ft_strlen(prefix));
	write(2, ": ", 2);
	write(2, error_message, ft_strlen(error_message));
	write(2, " ", 1);
	if (suffix)
		write(2, suffix, ft_strlen(suffix));
	write(2, "\n",1);
}

int	is_not_special(char ch)
{
	if (ch != ' ' && ch != '(' && ch != ')' && \
			ch != '<' && ch != '>' && ch != '|' && ch != '&')
		return (1);
	else
		return (0);
}

void	extract_the_phrase(char *dst, char *src, int *index)
{
	int i;
	int j;
	char tmp;

	i = *index;
	j = 0;
	while (src[i] && is_not_special(src[i]))
	{
		if (src[i] == '"' || src[i] == '\'')
		{
			tmp = src[i++];
			while (src[i] && src[i] != tmp)
			{
				if (tmp == '\'' && src[i] == '$')
					dst[j++] = src[i++] - '$' - 15;
				else
					dst[j++] = src[i++];
			}
			i++;
		}
		else
			dst[j++] = src[i++];
	}
	dst[j] = 0;
	*index = i;
}

void	restore_hidden_dollar(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == -15)
			str[i] = '$';
		i++;
	}
}

int	count_phrase_size(char *str, int i)
{
	int		result;
	char	tmp;

	result = 0;
	while(str[i] && is_not_special(str[i]))
	{
		if(str[i] == '"' || str[i] == '\'')
		{
			tmp = str[i++];
			while (str[i] && str[i] != tmp)
			{
				result++;
				i++;
			}
			i++;
		}
		else
		{
			result++;
			i++;
		}
	}
	return (result);
}

int	status_decoder(int status)
{
	int result;

	if (WIFEXITED(status))
		result = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		result = WTERMSIG(status) + 128;
	else if (WIFSTOPPED(status))
		result = WSTOPSIG(status) + 128;
	else
		result = 1;
	return (result);
}


/************************BLOCK MANIPULATION***************************/

void	block_init(block_t *block)
{
	block->type = 0;
	block->input_fd = 0;
	block->output_fd= 1;
	block->output_mode = 0;
	block->next_logic_elem = 0;
	block->exit_status = 0;
	block->exec_argv = 0;
	block->subsh_block_arr = 0;
	block->parsh_block = 0;
	//block->exec_arr = 0;
	block->next = 0;
	block->prev = 0;
	block->index = 0;
}

block_t *last_block(block_t *block_arr)
{
	block_t *ret_ptr;

	ret_ptr = block_arr;
	while (ret_ptr->next != 0)
		ret_ptr = ret_ptr->next;
	return (ret_ptr);
}

int	next_block_creator(block_t **p_block_arr, utils_t *utils)
{
	block_t	*new_block;
	block_t	*l_block;

	new_block = (block_t *)malloc(sizeof(block_t));
	if (new_block == 0)
		return(perror("block creation"), 1);
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

/*************************TOKENIZER*****************************/

int	space_processor(int *index, char *str)
{
	int result;

	result = 0;
	if (str[*index] == ' ')
		result = 1;
	while(str[*index] && str[*index] == ' ')
		(*index)++;
	return (result);
}


/*****h_doc_processor*****/

void	filename_creator(char *filename, int number)
{
	int i;
	int temp;

	i = 1;
	temp = number;
	while (temp >= 10 && ++i)
		temp /=10;
	filename[18 + i] = 0;
	while (i > 0)
	{
		filename[17 + i] = (char)(number % 10 + '0');
		i--;
		number /= 10;
	}

}

int	hd_temp_file_creator(char *filename)
{
	//char	filename[35];
	int		i;
	int 	fd;

	ft_strlcpy(filename, "minishel_temp_file", 35);
	i = 0;
	filename_creator(filename, i);
	while(access(filename, F_OK) == 0 && i <= 16)
		filename_creator(filename, ++i);
	if (i > 16)
		return(printf("bash: maximum here-document count exceeded\n"), 1);
	fd = open(filename, O_RDWR | O_CREAT | O_EXCL, 0644);
	if (fd == -1)
		return(my_perror("minishell", filename), fd);
	return (fd);
}



int	hd_mode_finder(char *str, int i)
{
	while(str[i] && is_not_special(str[i]))
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	hd_eof_extractor(utils_t *utils, int *index)
{
	int		size;
	char 	*ch;

	*index += 2;
	space_processor(index, utils->i_string);
	if (is_not_special(utils->i_string[*index]) == 0)
	{
		ch = &(utils->i_string[*index]);
		if ((*ch == '<' && *(ch + 1) == '<') || (*ch == '>' && *(ch + 1) == \
'>') || (*ch == '&' && *(ch + 1) == '&') || (*ch == '|' && *(ch + 1) == '|'))
		return (write(2, "minishell: syntax error near unexpected token '"\
						, 47), write(2, &ch, 2), write(2, "'\n", 2), 1);
		return (write(2, "minishell: syntax error near unexpected token '", \
						47), write(2, &ch, 1), write(2, "'\n", 2), 1);
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

int	write_to_file(int fd, utils_t *utils)
{
	char	*i_str;
	char	*tmp;

	i_str = readline(">");
	if (i_str == 0)
		return (perror("HD readline"), 1);
	while (ft_strcmp(i_str, utils->hd_eof) != 0)
	{
		if (utils->hd_mode == 0)
		{
			tmp = dollar_func(i_str, utils);
			free(i_str);
			i_str = tmp;
		}
		write(fd, i_str, ft_strlen(i_str));
		write(fd, "\n", 1);
		free (i_str);
		i_str = readline(">");
		if (i_str == 0)
			return (perror("HD readline"), 1);
	}
	free (i_str);
	return (0);
}

int	h_doc_processor(int *index, block_t **p_block_arr, utils_t *utils)
{
	block_t	*p_block;
	char	filename[35];

	if (utils->in_block == 0)
		if (next_block_creator(p_block_arr, utils) == 1)
			return (1);
	p_block = last_block(*p_block_arr);
	p_block->input_fd = hd_temp_file_creator(filename);
	if (p_block->input_fd == -1)
		return (1);
	if(hd_eof_extractor(utils, index) == 1)
		return (1);
	if (write_to_file(p_block->input_fd, utils) == 1)
		return (free(utils->hd_eof), 1);
	close(p_block->input_fd);
	p_block->input_fd = open(filename, O_RDONLY);
	return(free(utils->hd_eof), 0);
}

/*****s_input_processor*****/
int	s_input_processor2(int *index, block_t *p_block, utils_t *utils)
{
	char	filename[260];
	char	*new_filename;
	int		size;

	size = count_phrase_size(utils->i_string, *index);
	if (size > 256)
		return(perror("minishell: File name too long"), 1);
	extract_the_phrase(filename, utils->i_string, index);
	space_processor(index, utils->i_string);
	new_filename = dollar_func(filename, utils);
	restore_hidden_dollar(new_filename);
	p_block->input_fd = open(new_filename, O_RDONLY);
	if (p_block->input_fd == -1)
		return (my_perror("minishel", new_filename), 1);
	free (new_filename);
	return (0);
}

int	s_input_processor(int *index, block_t **p_block_arr, utils_t *utils)
{
	block_t	*p_block;
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
						, 47), write(2, &ch, 2), write(2, "'\n", 2), 1);
		return (write(2, "minishell: syntax error near unexpected token '", \
						47), write(2, &ch, 1), write(2, "'\n", 2), 1);
	}
	return(s_input_processor2(index, p_block, utils));
}

/*****s_output_processor*****/
int	s_output_processor2(int *index, block_t *p_block, utils_t *utils, int mode)
{
	char	filename[260];
	char	*new_filename;
	int		size;

	size = count_phrase_size(utils->i_string, *index);
	if (size > 256)
		return(perror("minishell: File name too long"), 1);
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
		return (my_perror("minishell", new_filename), 1);
	free(new_filename);
	return (0);
}

int	s_output_processor(int *index, block_t **p_block_arr, utils_t *utils, int mode)
{
	block_t	*p_block;
	char *ch;

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
						, 47), write(2, &ch, 2), write(2, "'\n", 2), 1);
		return (write(2, "minishell: syntax error near unexpected token '", \
						47), write(2, &ch, 1), write(2, "'\n", 2), 1);
	}
	return (s_output_processor2(index, p_block, utils, mode));
}

/*****command_processor*****/
int	count_words(char *str, int i)
{
	int		result;
	char	temp;

	result = 1;
	while((str[i] && is_not_special(str[i])) || str[i] == ' ')
	{
		if(str[i] == '"' || str[i] == '\'')
		{
			temp = str[i++];
			while (str[i] && str[i] != temp)
				i++;
		}
		else
			if (str[i] == ' ' && is_not_special(str[i + 1]))
				result++;
		i++;
	}
	return (result);
}

int	command_processor_error(int *index, utils_t *utils)
{
	char *temp;
	int  size;

	size = count_phrase_size(utils->i_string, *index);
	temp = (char *)malloc(sizeof(char) * (size +5));
	if (temp == 0)
		return (my_perror("minishell", "command processor error message"), 1);
	extract_the_phrase(temp, utils->i_string, index);
	write(2, "minishell: Syntax error near unexpected token '", 47);
	write(2, temp, ft_strlen(temp));
	write(2, "'\n", 2);
	free (temp);
	return (0);
}

int	command_processor2(int *index, block_t *p_block, utils_t *utils)
{
	int		size;
	char	*temp;
	int		i;

	i = 0;
	while (p_block->exec_argv[i] != 0)
		i++;
	while(utils->i_string[*index] && is_not_special(utils->i_string[*index]))
	{
		size = count_phrase_size(utils->i_string, *index);
		temp = (char *)malloc(sizeof(char) * (size + 5));
		if (temp == 0)
			return(/*free(p_block->exec_argv), */my_perror("minishell", \
						"command_processor"), 1);
		extract_the_phrase(temp, utils->i_string, index);
		p_block->exec_argv[i] = dollar_func(temp, utils);
		if (p_block->exec_argv[i] == 0)
			return (/*free(p_block->exec_argv), */free(temp), \
					my_perror("minishell", " command_processor_dollar"), 1);
		free(temp);
		restore_hidden_dollar(p_block->exec_argv[i++]);
		space_processor(index, utils->i_string);
	}
	return (0);
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
		temp[i] = (char *)malloc(sizeof(char) * (ft_strlen((*exec_argv)[i]) + 5));
		ft_strlcpy(temp[i], (*exec_argv)[i], ft_strlen((*exec_argv)[i]) + 5);
		i++;
	}
	i = 0;
	while((*exec_argv)[i])
		free((*exec_argv)[i++]);
	free(*exec_argv);
	*exec_argv = temp;
	return (0);
}

int	command_processor(int *index, block_t **p_block_arr, utils_t *utils)
{
	block_t	*p_block;
	int		size;

	if (utils->in_block == 0)
		if (next_block_creator(p_block_arr, utils) == 1)
			return (1);
	p_block = last_block(*p_block_arr);
	if (p_block->exec_argv == (char **)1)
		return(command_processor_error(index, utils), 1);
	size = count_words(utils->i_string, *index);
	if (p_block->exec_argv != 0)
	{
		if (new_exec_argv_creator(&(p_block->exec_argv), size) == 1)
			return (1);
	}
	else
		p_block->exec_argv = (char **)ft_calloc(size + 5, sizeof(char *));
	if (p_block->exec_argv == 0)
		return (my_perror("minishell", " command_processor"), 1);
	p_block->type = EXEC;
	return (command_processor2(index, p_block, utils));
}

/*****logical_and_processor*****/
int	logical_and_processor(int *index, block_t **p_block_arr, utils_t *utils)
{
	block_t	*p_block;

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
int	logical_or_processor(int *index, block_t **p_block_arr, utils_t *utils)
{
	block_t	*p_block;

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

int	pipe_processor(int *index, block_t **p_block_arr, utils_t *utils)
{
	block_t *p_block;

	if (utils->in_block == 0)
		return (write(2, "minishell: Syntax error near unexpected token |\n", \
					48), 1);
	p_block = last_block(*p_block_arr);
	p_block->next_logic_elem = MY_PIPE;
	utils->in_block = 0;
	*index += 1;
	space_processor(index, utils->i_string);
	return (0);
}


/*******parenthesis_open*******/
int	parenthesis_open(int *index, block_t ***p_p_block_arr, utils_t *utils)
{
	block_t *p_block;

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
int	parenthesis_close(int *index, block_t ***p_p_block_arr, utils_t *utils)
{
	block_t *p_block;

	*p_p_block_arr = utils->parsh_block;
	p_block = last_block(**p_p_block_arr);
	utils->parsh_block = p_block->parsh_block;
	(*index)++;
	space_processor(index, utils->i_string);
	utils->in_block = 1;
	return (0);
}

int	tokenizer(block_t **p_block_arr,  utils_t *utils)
{
	int	i;
	int	ret_val;

	i = 0;
	ret_val = 0;
	while (utils->i_string[i] && ret_val == 0)
	{
		if (utils->i_string[i] == ' ')
			utils->new_word = space_processor(&i, utils->i_string);
		else if (utils->i_string[i] == '<' && utils->i_string[i + 1] == '<' )
			ret_val = h_doc_processor(&i, p_block_arr, utils);
		else if (utils->i_string[i] == '<')
			ret_val = s_input_processor(&i, p_block_arr, utils);
		else if (utils->i_string[i] == '>' && utils->i_string[i + 1] == '>' )
			ret_val = s_output_processor(&i, p_block_arr, utils, 0);
		else if (utils->i_string[i] == '>')
			ret_val = s_output_processor(&i, p_block_arr, utils, 1);
		else if (utils->i_string[i] == '&' && utils->i_string[i + 1] == '&')
			ret_val = logical_and_processor(&i, p_block_arr, utils);
		else if (utils->i_string[i] == '|' && utils->i_string[i + 1] == '|')
			ret_val = logical_or_processor(&i, p_block_arr, utils);
		else if (utils->i_string[i] == '|')
			ret_val = pipe_processor(&i, p_block_arr, utils);
		else if (utils->i_string[i] == '(')
			ret_val = parenthesis_open(&i, &p_block_arr, utils);
		else if (utils->i_string[i] == ')')
			ret_val = parenthesis_close(&i, &p_block_arr, utils);
		else
			ret_val = command_processor(&i, p_block_arr, utils);
	}
	return (ret_val);
}


/***********************EXECUTOR****************************/

/***regular_exec***/
void	exec_compose_cleanup(char **paths)
{
	int j;

	j = 0;
	while (paths[j])
		free(paths[j++]);
	free(paths);
}

char	*exec_compose2(char *exec, char **paths)
{
	int		i;
	char	*temp;
	char	*result;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i++], "/");
		if (temp == 0)
			return (exec_compose_cleanup(paths), (char *)0);
		result = ft_strjoin(temp, exec);
		free(temp);
		if (result == 0)
			return (exec_compose_cleanup(paths), (char *)0);
		if (access(result, F_OK) == 0)
			return (exec_compose_cleanup(paths), result);
	}
	return (exec_compose_cleanup(paths), exec);
}

char	*exec_compose(char *exec, char **env)
{
	int		i;
	char	**paths;

	i = 0;
	if (exec == 0)
		return (0);
	if (ft_strchr(exec, (int)'/'))
		return (exec);
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (env[i] == 0)
		return (exec);
	paths = ft_split(&(env[i][5]), ':');
	if (!paths)
		return (0);
	return (exec_compose2(exec, paths));

}

int	reg_exec_child(block_t *block, utils_t *utils, char *exec)
{

	if (dup2(block->input_fd, 0) == -1 || dup2(block->output_fd, 1) == -1)
		return (my_perror("minishell", exec), free(exec), \
				full_clean(block, utils), 1);
	if (block->input_fd != 0)
		close(block->input_fd);
	if (block->output_fd != 1)
		close(block->output_fd);
	execve(exec, block->exec_argv, utils->env);
	return(my_perror("minishell: ", exec), free(exec), \
		full_clean(block, utils), 1);
}

void	exit_status_processing(block_t *block, utils_t *utils)
{
	utils->last_exit_status = block->exit_status;
	if ((block->exit_status == 0 && block->next_logic_elem == AND_AND) || \
		(block->exit_status != 0 && block->next_logic_elem == OR_OR))
		utils->ok_to_cnt = 1;
	else
		utils->ok_to_cnt = 0;
}

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
	//else if (ft_strcmp(exec, "exit") == 0)
	//	return (7);
	else
		return (0);
}

int	builtin_fd_chng(int *fd, block_t *block)
{
	int	temp[2];

	fd[0] = dup(0);
	fd[1] = dup(1);
	if (fd[0] == -1 || fd[1] == -1)
		return(my_perror("minishell: ", "fd_change_for_builtin"), 1);
	temp[0] = dup2(block->input_fd, 0);
	temp[1] = dup2(block->output_fd, 1);
	if (temp[0] == -1 || temp[1] == -1)
		return(my_perror("minishell: ", "fd_change_for_builtin"), 1);
	if (block->input_fd != 0)
		close(block->input_fd);
	if (block->output_fd != 1)
		close(block->output_fd);
	return (0);
}

int	builtin_fd_revert(int *fd)
{
	int temp[2];

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

int	run_builtin(block_t *block, utils_t *utils)
{
	int	type;

	block->exit_status = 0;
	type = is_builtin(block->exec_argv[0]);
	if (type == 1)
		echo(block->exec_argv, utils);		/*****FOR SUREN!!!!!*****/
	else if (type == 3)
		block->exit_status = cd(block->exec_argv[1], utils);
	else if (type == 6)
		env_print(utils);
	else if (type == 4)
		export_f(utils, block->exec_argv); // sxala ed argv-y te che ashxatuma :)
	else if (type == 5)
		unset_f(utils ,block->exec_argv);
	else if (type == 2)
		pwd(utils);
	//else  if (type == 7)
	//	exit(block, utils);
	exit_status_processing(block, utils);
	return (block->exit_status);
}

int	waiting_or_no(int pid, char *exec, block_t *block, utils_t *utils)
{
	int temp;

	if (block->next_logic_elem != MY_PIPE)
	{
		if (waitpid(pid, &(block->exit_status), 0) != pid)
			return (my_perror("minishell: ", exec), free(exec), 1);
		block->exit_status = status_decoder(block->exit_status);
		exit_status_processing(block, utils);
		while (wait(&temp) != -1);
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

int	regular_exec(block_t *block, utils_t *utils)
{
	char	*exec;
	int		pid;
	int		ret_val;
	int		fd[2];
	
	if (is_builtin(block->exec_argv[0]))
	{
		ret_val = !(!builtin_fd_chng(fd, block) && !run_builtin(block, utils));
		return (!(!builtin_fd_revert(fd) && !ret_val));
	}
	exec = exec_compose(block->exec_argv[0], utils->env);
	if (exec == 0)
		return (my_perror("minishell: ", "exec_compose"), 1);

	pid = fork();
	if (pid == -1)
		return (my_perror("minishell: ", exec), 1);
	else if (pid == 0)
		exit (reg_exec_child(block, utils, exec));


	if (block->input_fd != 0)
		close(block->input_fd);
	if (block->output_fd != 1)
		close(block->output_fd);

	return (waiting_or_no(pid, exec, block, utils));
}

/***regular_subshell***/
int	subsh_waiting_or_no(int pid, block_t *block, utils_t *utils)
{
	int temp;

	if (block->next_logic_elem != MY_PIPE)
	{
		if (waitpid(pid, &(block->exit_status), 0) != pid)
			return (my_perror("minishell", ""), 1);
		exit_status_processing(block, utils);
		printf("balu");
		while (wait(&temp) != -1)
			printf("hello");
	}
	else
	{
		block->exit_status = 0;
		utils->last_exit_status = 0;
		utils->ok_to_cnt = 1;
	}
	return (0);
}

int	regular_subshell(block_t *block, utils_t *utils)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (my_perror("minishell: ", "subshell"), 1);
	else if (pid == 0)
	{
		if (dup2(block->input_fd, 0) == -1 || dup2(block->output_fd, 1) == -1)
			return (my_perror("minishell", "subhsell"), \
				full_clean(block, utils), 1);
		if (block->input_fd != 0)
			close(block->input_fd);
		if (block->output_fd != 1)
			close(block->output_fd);
		executor(block->subsh_block_arr, utils);
		full_clean(block, utils);
		exit (utils->last_exit_status);
	}
	if (block->input_fd != 0)
		close(block->input_fd);
	if (block->output_fd != 1)
		close(block->output_fd);
	return (subsh_waiting_or_no(pid, block, utils));
}

/***pipe_exec***/

int	pipes_creator(block_t *block)
{
	int fd[2];

	while(block->next_logic_elem == MY_PIPE)
	{
		if (pipe(fd) == -1)
			return (my_perror("minishell: ", "pipes_creator"), 1);
		if (block->output_fd == 1)
			block->output_fd = fd[1];
		else
			close(fd[1]);
		if (block->next->input_fd == 0)
			block->next->input_fd = fd[0];
		else
			close(fd[0]);
		block = block->next;
	}
	return (0);
}

int	pipe_exec(block_t *block, utils_t *utils)
{

	if (pipes_creator(block) == 1)
		return(1);
	while (block != 0 && (block->next_logic_elem == MY_PIPE || \
				block->prev->next_logic_elem == MY_PIPE))
	{
		if (block->type == EXEC)
		{
			if (regular_exec(block, utils) == 1)
				return (1);
			block = block->next;
		}
		else if (block->type == SUBSH)
		{
			if (regular_subshell(block, utils) == 1)
				return (1);
			block = block->next;
		}
	}
	return (0);	
}

int executor(block_t *block, utils_t *utils)
{
	int ret_val;

	ret_val = 0;
	while (block != 0 && utils->ok_to_cnt && ret_val == 0)
	{
		if (block->type == EXEC && block->next_logic_elem != MY_PIPE)
		{
			ret_val = regular_exec(block, utils);
			block = block->next;
		}
		else if (block->type == SUBSH && block->next_logic_elem != MY_PIPE)
		{
			ret_val = regular_subshell(block, utils);
			block = block->next;
		}
		else if (block->next_logic_elem == MY_PIPE)
		{
			ret_val = pipe_exec(block, utils);
			while (block != 0 && (block->next_logic_elem == MY_PIPE || \
				block->prev->next_logic_elem == MY_PIPE))
				block = block->next;
		}
	}
	return (ret_val);
}



/**********************INIT_INIT***************************/


int	init_init(utils_t *utils, char **env)
{
	utils->env = env;
	utils->new_word = 1;
	utils->in_block = 0;
	utils->i_string = 0;
	utils->hd_eof = 0;
	utils->hd_mode = 0;
	utils->i_string = 0;
	utils->parsh_block = 0;
	utils->ok_to_cnt = 1;
	utils->last_exit_status = 0;
	utils->shell = malloc(sizeof(t_shell));
	if(!utils->shell)
		return(1);
	utils->shell->duplicate_env = NULL;
	duplicate_env(utils->shell, env);
	return (0);
}

int main(int argc, char *argv[], char *env[])
{
	block_t	*block_arr;
	utils_t	utils;

	if (argc > 1)
		argv[1] = 0;
	if (init_init(&utils, env) == 1)
		return (1);
	block_arr = 0;
	while (1)
	{
		get_string(&utils);
		if (syntax_check(&utils) == 0)
			if (tokenizer(&block_arr, &utils) == 0)
				if (var_substitute(block_arr, &utils) == 0)
					executor(block_arr, &utils);
		cleaner(&block_arr, &utils);
	}
}
