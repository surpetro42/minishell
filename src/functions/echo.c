/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:37:10 by surpetro          #+#    #+#             */
/*   Updated: 2024/10/07 20:19:41 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


/* ~~~~~~~~~~~ uxxelu ban unem mejy  bayc verjum ed ~~~~~~~~~~~ */


void	echo_quotation(char *str)
{
	int i = 0;
	if(str[i] == '"' && str[i] == '\'')
	{
		while (str[i] != '"' && str[i] != '\'')
		{
			printf("%c", str[i]);
			i++;
		}
	}
}

void	echo(char **argv, utils_t *utils)
{
	(void)utils;
	int i;
	int l;
	int buff;

	i = 1;
	buff = 0;
	if (argv[1])
	{
		l = 0;
		if (argv[1][0] == '-' && argv[1][1] == 'n')
		{
			l++;
			buff = l;
			while (argv[i][buff] == 'n')
				buff++;
			if(argv[i][buff] > 32 && argv[i][buff] != 'n')
			{
				l = buff;
				while (argv[i])
				{
					if (argv[i + 1] != NULL)
						printf("%s ", argv[i]);
					else
						printf("%s\n", argv[i]);
					i++;
				}
			}
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
		else
		while (argv[i])
		{
			if (argv[i + 1] != NULL)
				printf("%s ", argv[i]);
			else
				printf("%s\n", argv[i]);
			i++;
		}
	}
}
