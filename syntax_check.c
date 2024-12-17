/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:14:34 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/07 14:17:32 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

/************SYNTAX_CHECK************/

int	find_the_pair_quote(char *i_string, int *index)
{
	char	quote;
	int		i;

	i = *index;
	quote = i_string[i];
	i++;
	while (i_string[i] && i_string[i] != quote)
		i++;
	*index = i;
	if (i_string[i] == 0)
		return (1);
	else
		return (0);
}

int	quotes_checker(t_utils *utils)
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

int	parenthesis_checker(t_utils *utils)
{
	int	i;
	int	p_count;

	i = 0;
	p_count = 0;
	while (p_count >= 0 && utils->i_string[i])
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

int	syntax_check(t_utils *utils)
{
	if (quotes_checker(utils) == 1 || parenthesis_checker(utils) == 1)
	{
		utils->last_exit_status = 1;
		return (1);
	}
	return (0);
}
