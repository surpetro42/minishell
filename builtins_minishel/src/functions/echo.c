/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:37:10 by surpetro          #+#    #+#             */
/*   Updated: 2024/11/15 21:22:47 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishel.h"

void	print_echo(char **argv, int i)
{
	while (argv[i])
	{
		if (argv[i + 1] != NULL)
			printf("%s ", argv[i]);
		else
			printf("%s\n", argv[i]);
		i++;
	}
}

void	part_new_line(char **argv, int i, int l)
{
	while (argv[i][l] == 'n')
		l++;
	if (argv[i][l] > 32 && argv[i][l] != 'n')
		print_echo(argv, 1);
	else
	{
		while (argv[++i])
		{
			if (argv[i + 1] != NULL)
				printf("%s ", argv[i]);
			else
				printf("%s", argv[i]);
		}
	}
}

int	end_new_line(char **argv)
{
	int i = 0;
	int l;
	while (argv[i])
	{
		l = 1;
		if(argv[i][0] == '-')
			while (argv[i][l] == 'n')
				l++;
		if (argv[i][l] >= 32 && argv[i][l] != 'n')
			return i;
		else
		 	i++;
	}
	return i;
}

void	echo(char **argv, utils_t *utils)
{
	(void)utils;
	int	i;

	i = 1;
	if(argv[1])
	{
		if ((argv[1][0] == '-' && argv[1][1] == 'n'))
		{
			i = end_new_line(&argv[1]);
			part_new_line(argv, i, 1);
		}
		else
			print_echo(argv, 1);
	}
	else
		printf("\n");
}
