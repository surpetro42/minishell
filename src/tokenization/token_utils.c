/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:26:27 by surpetro          #+#    #+#             */
/*   Updated: 2024/09/11 21:19:26 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	quotation(char *str)
{
	int i = 0;
	int count_double_quote = 0;
	int count_apostrophe = 0;

	while (str[i])
	{
		if (str[i] == '"')
		{
			count_double_quote++;
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if(str[i] == '"')
				count_double_quote++;
		}
		if (str[i] == '\'')
		{
			count_apostrophe++;
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if(str[i] == '\'')
				count_apostrophe++;
		}
		if (str[i] != '\0')
			i++;
	}
	if(count_double_quote % 2 != 0 || count_apostrophe % 2 != 0)
		exit(write(1, "--> Quotation Error\n", 19));
		
}

void	ft_strncpy(char *dst, char *src, int len)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && i + 1 < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	len_operator(char *str)
{
	int i = 0;
	if(!str)
		return -1;
	if(str[i] == '|')
		return 1;
	if(str[i] == '>')
	{
		if(str[i + 1] && str[i + 1] == '>')
			return 2;
		return 1;
	}
	if(str[i] == '<')
	{
		if(str[i + 1] && str[i + 1] == '<')
			return 2;
		return 1;
	}
	return i;
}

int	is_operator(char *str)
{
	int len;
	
	len = len_operator(str);
	if(len == 0)
		return 0;
	else
		return 1;
}

int	gettype(char *str)
{
	int i = 0;

	if(!str)
		return -1;
	if(str[i] == '|')
		return PIPE;
	if(str[i] == '>')
	{
		if(str[i + 1] && str[i + 1] == '>')
			return APPEND_OUTPUT_REDIRECTION;
		return OUTPUT_REDIRECTION;
	}
	if(str[i] == '<')
	{
		if(str[i + 1] && str[i + 1] == '<')
			return HERE_DOCUMENT;
		return INPUT_REDIRECTION;
	}
	return STRING;
}

void	token_utils(t_shell *shell)
{
	t_arguments *iter;
	t_arguments start;
	int i = 0;
	int len = 0;
	
	iter = &start;
	quotation(shell->input);
	while (shell->input && shell->input[i])
	{
		len = 0;
		while (shell->input && shell->input[i] > 32)
		{
			if (len == 0 && is_operator(&shell->input[i]) == 1)
			{
				len = len_operator(&shell->input[i]);
				i += len;
				break;
			}
			else if (len != 0 && is_operator(&shell->input[i]) == 1)
				break;
			else
				len++;
			i++;
		}
		iter->next = malloc(sizeof(t_arguments));
		if(!iter->next)
			return ;
		iter->value = malloc(sizeof(len) + 1);
		if(!iter->value)
			return ;
		printf("%d\n", len);
		ft_strncpy(iter->value, &shell->input[i], len);
		iter->value[len] = '\0';
		printf("iter->value == %s\n",iter->value);
		iter = iter->next;
		if(shell->input[i] <= 32)
			i++;
	}
	iter->next = NULL;
	shell->arguments = start.next;
}