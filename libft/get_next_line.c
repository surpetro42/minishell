/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:23:34 by ayeganya          #+#    #+#             */
/*   Updated: 2024/06/10 11:59:59 by ayeganya         ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	static t_fd_lst	*ptr_cache = 0;
	t_gnl_misc		misc;

	if (fd < 0)
		return (0);
	misc.result = (char *)malloc(BUFFER_SIZE +1);
	if (!misc.result)
		return (0);
	*(misc.result) = 0;
	if (cache_extract(&ptr_cache, fd, misc.result))
		return (misc.result);
	misc.status = 1;
	while (misc.status == 1)
	{
		extractor(fd, misc.buf, &(misc.status));
		str_expander(misc.buf, &(misc.result), &(misc.status));
	}
	str_cache(misc.buf, &(misc.result), &ptr_cache, fd);
	if (ft_strlen(misc.result) == 0 || misc.status == -1)
	{
		free (misc.result);
		return (0);
	}
	return (misc.result);
}

void	extractor(int fd, char *buf, int *status)
{
	int	br;
	int	i;

	br = read(fd, buf, BUFFER_SIZE);
	if (br == -1)
	{
		*status = -1;
		*buf = 0;
		return ;
	}
	buf[br] = 0;
	i = 0;
	while (i < br)
	{
		if (buf[i] == '\n' || buf[i] == 0)
			break ;
		i++;
	}
	if (i < BUFFER_SIZE || BUFFER_SIZE == 0)
		*status = 0;
	else
		*status = 1;
}

void	str_expander(char *buf, char **result, int *status)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	temp = (char *)malloc(ft_strlen(buf) + ft_strlen(*result) + 1);
	if (!temp)
	{
		*status = -1;
		return ;
	}
	while ((*result)[i] && ++i)
		temp[i - 1] = (*result)[i - 1];
	while (buf[j] && buf[j] != '\n' && ++i && ++j)
		temp[i -1] = buf[j -1];
	if (buf[j] == '\n')
	{
		temp[i] = '\n';
		temp[i + 1] = 0;
	}
	else
		temp[i] = 0;
	free(*result);
	*result = temp;
}

void	str_cache(char *buf, char **result, t_fd_lst **cache, int fd)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n' && buf[i + 1] != 0)
		{
			if (cache_writer(cache, buf + i + 1, fd) == -1)
			{
				free (*result);
				*result = 0;
			}
			break ;
		}
		i++;
	}
}

int	cache_extract(t_fd_lst **ptr_ptr_cache, int fd, char *str)
{
	int			i;
	t_fd_lst	*ptr_cache;

	i = 0;
	if (!str)
		return (1);
	ptr_cache = *ptr_ptr_cache;
	while (ptr_cache && ptr_cache->fd != fd && ptr_cache->next != 0)
		ptr_cache = ptr_cache->next;
	if (ptr_cache && ptr_cache->fd == fd)
	{
		while (ptr_cache->str[i] && ptr_cache->str[i] != '\n' && ++i)
			str[i - 1] = ptr_cache->str[i - 1];
		if (ptr_cache->str[i] == '\n')
			return (frankenshtein(ptr_cache->str, &(str[i])));
		else
		{
			str[i] = 0;
			cache_cleaner(ptr_ptr_cache, fd);
		}
	}
	return (0);
}
/*
#include <stdio.h>
int main()
{
	int fd[10];
	fd[0] = open("../gnlTester/files/41_with_nl", O_RDWR);
	fd[1] = open("../gnlTester/files/42_with_nl", O_RDWR);
	fd[2] = open("../gnlTester/files/43_with_nl", O_RDWR);
	fd[3] = open("../gnlTester/files/nl", O_RDWR);
	printf("%s", get_next_line(1000));
	printf("%s", get_next_line(fd[0]));
	printf("%s", get_next_line(1001));
	printf("%s", get_next_line(fd[1]));
	printf("%s", get_next_line(1002));
	printf("%s", get_next_line(fd[2]));
	printf("%s", get_next_line(1003));
	printf("%s", get_next_line(fd[0]));
	printf("%s", get_next_line(1004));
	printf("%s", get_next_line(fd[1]));
	printf("%s", get_next_line(1005));
	printf("%s", get_next_line(fd[2]));
	printf("%s", get_next_line(fd[0]));
	printf("%s", get_next_line(fd[1]));
	printf("%s", get_next_line(fd[2]));
	printf("%s", get_next_line(1006));
	printf("%s", get_next_line(fd[3]));
	printf("%s", get_next_line(1007));
	printf("%s", get_next_line(fd[3]));
}*/
