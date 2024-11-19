/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:25:16 by ayeganya          #+#    #+#             */
/*   Updated: 2024/05/19 11:25:35 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*get_next_line(int fd);
int			cache_extract(t_fd_lst **ptr_ptr_cache, int fd, char *str);
void		extractor(int fd, char *buf, int *status);
void		str_expander(char *additive, char **result, int *status);
void		str_cache(char *buf, char **result, t_fd_lst **cache, int fd);
int			cache_writer(t_fd_lst **ptr_ptr_cache, char *str, int fd);
void		cache_cleaner(t_fd_lst **ptr_ptr_cache, int fd);
void		add_new_line(char *str, char *temp);
t_fd_lst	*cache_element_creator(int fd);
int			frankenshtein(char *str, char *add_nl);

int	cache_writer(t_fd_lst **ptr_ptr_cache, char *str, int fd)
{
	int			i;
	t_fd_lst	*temp_ptr;

	if (!*ptr_ptr_cache)
		*ptr_ptr_cache = cache_element_creator(fd);
	if (!*ptr_ptr_cache)
		return (-1);
	temp_ptr = *ptr_ptr_cache;
	while (temp_ptr->fd != fd && temp_ptr->next != 0)
		temp_ptr = temp_ptr->next;
	if (temp_ptr->fd != fd)
	{
		temp_ptr->next = cache_element_creator(fd);
		if (!temp_ptr->next)
			return (-1);
		temp_ptr = temp_ptr->next;
	}
	i = 0;
	while (str[i] && ++i)
		temp_ptr->str[i - 1] = str[i - 1];
	temp_ptr->str[i] = 0;
	return (0);
}

void	cache_cleaner(t_fd_lst **ptr_ptr_cache, int fd)
{
	t_fd_lst	*temp;
	t_fd_lst	*iter;

	if ((*ptr_ptr_cache)->fd == fd)
	{
		free((*ptr_ptr_cache)->str);
		temp = *ptr_ptr_cache;
		*ptr_ptr_cache = (*ptr_ptr_cache)->next;
		free(temp);
		return ;
	}
	iter = *ptr_ptr_cache;
	while (iter->next != 0 && iter->next->fd != fd)
		iter = iter->next;
	if (iter->next->fd == fd)
	{
		free(iter->next->str);
		temp = iter->next;
		iter->next = iter->next->next;
		free (temp);
	}
}

t_fd_lst	*cache_element_creator(int fd)
{
	t_fd_lst	*cache;

	cache = (t_fd_lst *)malloc(sizeof(t_fd_lst));
	if (!cache)
		return (0);
	cache->fd = fd;
	cache->str = (char *)malloc(BUFFER_SIZE + 1);
	if (!cache->str)
	{
		free(cache);
		return (0);
	}
	cache->next = 0;
	return (cache);
}

int	frankenshtein(char *str, char *add_nl)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	i++;
	while (str[i])
	{
		str[j] = str[i];
		j++;
		i++;
	}
	str[j] = 0;
	add_nl[0] = '\n';
	add_nl[1] = 0;
	return (1);
}
/*
int	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}*/
