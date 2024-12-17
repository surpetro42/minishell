/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:30:36 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/15 12:35:42 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int	matches(char *w_str, char *fname)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (w_str[i] != 0 && fname[j] != 0)
	{
		if (w_str[i] == '*')
		{
			while (w_str[i] == '*')
				i++;
			while (fname[j] && w_str[i] != fname[j])
				j++;
			continue ;
		}
		if (w_str[i] != fname[j])
			return (0);
		i++;
		j++;
	}
	while (w_str[i] == '*')
		i++;
	if (w_str[i] != fname[j])
		return (0);
	return (1);
}

int	add_match(t_file_list **p_file_list, char *fname)
{
	t_file_list	*file_list;

	if (*p_file_list == 0)
	{
		*p_file_list = (t_file_list *)malloc(sizeof(t_file_list));
		if (*p_file_list == 0)
			return (my_perror("minishell", "add_match"), 1);
		file_list = *p_file_list;
	}
	else
	{
		file_list = *p_file_list;
		while (file_list->next != 0)
			file_list = file_list->next;
		file_list->next = (t_file_list *)malloc(sizeof(t_file_list));
		if (file_list->next == 0)
			return (my_perror("minishell", "add_match"), 1);
		file_list = file_list->next;
	}
	ft_strlcpy(file_list->filename, fname, NAME_MAX);
	file_list->next = 0;
	return (0);
}

int	argv_find_and_replace(char ***p_argv, int *i, DIR *dir)
{
	t_file_list		*file_list;
	struct dirent	*entry;
	int				match_nbr;

	file_list = 0;
	entry = readdir(dir);
	match_nbr = 0;
	while (entry != 0)
	{
		if (matches((*p_argv)[*i], entry->d_name) && \
				check_first_dot((*p_argv)[*i], entry->d_name) && ++match_nbr)
			if (add_match(&file_list, entry->d_name) == 1)
				return (1);
		entry = readdir(dir);
	}
	if (file_list == 0 && ++(*i))
		return (0);
	if (argv_replace(p_argv, *i, file_list, match_nbr) == 1)
		return (1);
	*i += match_nbr;
	file_list_clean(file_list);
	return (0);
}

int	no_asterisk(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*')
			return (0);
		if (str[i] == -17)
			str[i] = '*';
		i++;
	}
	return (1);
}

int	argv_wildcard_processor(t_block *block)
{
	int	i;
	DIR	*dir;

	i = 1;
	no_asterisk(block->exec_argv[0]);
	dir = opendir(".");
	if (dir == 0)
		return (my_perror("minishell", 0), 1);
	while (block->exec_argv[i] != 0)
	{
		if (no_asterisk(block->exec_argv[i]) && ++i)
			continue ;
		if (argv_find_and_replace(&(block->exec_argv), &i, dir) == 1)
			return (1);
		closedir(dir);
		dir = opendir(".");
	}
	closedir(dir);
	return (0);
}
