/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:27:45 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/07 14:49:27 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

void	restore_hidden_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
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
	while (str[i] && is_not_special(str[i]))
	{
		if (str[i] == '"' || str[i] == '\'')
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
	int	result;

	if (WIFEXITED(status))
		result = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		result = WTERMSIG(status) + 128;
		if (result == 131)
			printf("Quit: %d\n", result - 128);
	}
	else if (WIFSTOPPED(status))
		result = WSTOPSIG(status) + 128;
	else
		result = 1;
	return (result);
}

void	file_list_clean(t_file_list *file_list)
{
	t_file_list	*temp;

	while (file_list)
	{
		temp = file_list;
		file_list = file_list->next;
		free(temp);
	}
}

void	filename_creator(char *filename, int number)
{
	int	i;
	int	temp;

	i = 1;
	temp = number;
	while (temp >= 10 && ++i)
		temp /= 10;
	filename[18 + i] = 0;
	while (i > 0)
	{
		filename[17 + i] = (char)(number % 10 + '0');
		i--;
		number /= 10;
	}
}
