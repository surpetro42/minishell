/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:39:43 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/07 14:41:03 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

void	clean_argv_memory(char **argv)
{
	int	i;

	if (argv == 0)
		return ;
	i = 0;
	while (argv[i] != 0)
		free(argv[i++]);
	free(argv);
}

int	argv_replace_1(char ***p_argv, int i, char **temp)
{
	int	j;

	j = 0;
	while (j < i)
	{
		temp[j] = (char *)malloc(sizeof(char) * (ft_strlen((*p_argv)[j]) + 1));
		if (temp[j] == 0)
			return (clean_argv_memory(temp), \
					my_perror("minishell", "argv_replace_1"), 1);
		ft_strlcpy(temp[j], (*p_argv)[j], ft_strlen((*p_argv)[j]) + 1);
		j++;
	}
	return (0);
}

int	argv_replace_2(char **temp, int j, t_file_list *file_list)
{
	while (file_list != 0)
	{
		temp[j] = (char *)malloc(sizeof(char) * \
				(ft_strlen(file_list->filename) + 1));
		if (temp[j] == 0)
			return (clean_argv_memory(temp), \
				my_perror("minishell", "argv_replace_2"), 1);
		ft_strlcpy(temp[j++], file_list->filename, \
				ft_strlen(file_list->filename) + 1);
		file_list = file_list->next;
	}
	return (0);
}

int	argv_replace_3(char **temp, int i, int match_nbr, char ***p_argv)
{
	int	j;

	j = i + match_nbr - 1;
	while ((*p_argv)[i] != 0)
	{
		temp[j] = (char *)malloc(sizeof(char) * (ft_strlen((*p_argv)[i]) + 1));
		if (temp[j] == 0)
			return (clean_argv_memory(temp), \
					my_perror("minishell", "argv_replace_3"), 1);
		ft_strlcpy(temp[j], (*p_argv)[i], ft_strlen((*p_argv)[i]) + 1);
		i++;
		j++;
	}
	temp[j] = 0;
	return (0);
}

int	argv_replace(char ***p_argv, int i, t_file_list *file_list, int match_nbr)
{
	int		j;
	char	**temp;

	j = 0;
	while ((*p_argv)[j] != 0)
		j++;
	temp = (char **)malloc(sizeof(char *) * (j + match_nbr));
	if (temp == 0)
		return (my_perror("minishell", "argv_replace"), 1);
	if (argv_replace_1(p_argv, i, temp) == 1)
		return (1);
	if (argv_replace_2(temp, i, file_list) == 1)
		return (1);
	if (argv_replace_3(temp, i + 1, match_nbr, p_argv) == 1)
		return (1);
	clean_argv_memory(*p_argv);
	*p_argv = temp;
	return (0);
}
