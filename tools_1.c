/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:18:36 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/07 15:14:35 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

void	special_case(char *dst, char *src, int i, int *j_index)
{
	i--;
	while ((src[i] >= '0' && src[i] <= '9') || (src[i] >= 'a' && src[i] <= \
				'z') || (src[i] >= 'A' && src[i] <= 'Z'))
		i--;
	if (src[i] != '$')
		return ;
	dst[*j_index] = -16;
	(*j_index)++;
}

void	sub_extract_the_phrase(char *dst, char *src, int *i, int *j)
{
	char	tmp;

	if (src[*i] == '"')
		special_case(dst, src, *i, j);
	tmp = src[(*i)++];
	while (src[*i] && src[*i] != tmp)
	{
		if (tmp == '\'' && src[*i] == '$')
			dst[(*j)++] = src[(*i)++] - '$' - 15;
		else
			dst[(*j)++] = src[(*i)++];
	}
	if (tmp == '"')
		special_case(dst, src, *i, j);
	(*i)++;
}

void	sub_extract_the_phrase_2(char *dst, char *src, int *i, int *j)
{
	char	tmp;

	if (src[*i] == '"')
		special_case(dst, src, *i, j);
	tmp = src[(*i)++];
	while (src[*i] && src[*i] != tmp)
	{
		if (tmp == '\'' && src[*i] == '$')
			dst[(*j)++] = src[(*i)++] - '$' - 15;
		else if ((tmp == '\'' || tmp == '"') && src[*i] == '*')
			dst[(*j)++] = src[(*i)++] - '*' - 17;
		else
			dst[(*j)++] = src[(*i)++];
	}
	if (tmp == '"')
		special_case(dst, src, *i, j);
	(*i)++;
}

void	extract_the_phrase_2(char *dst, char *src, int *index)
{
	int		i;
	int		j;

	i = *index;
	j = 0;
	while (src[i] && is_not_special(src[i]))
	{
		if (src[i] == '"' || src[i] == '\'')
			sub_extract_the_phrase_2(dst, src, &i, &j);
		else
			dst[j++] = src[i++];
	}
	dst[j] = 0;
	*index = i;
}

void	extract_the_phrase(char *dst, char *src, int *index)
{
	int		i;
	int		j;

	i = *index;
	j = 0;
	while (src[i] && is_not_special(src[i]))
	{
		if (src[i] == '"' || src[i] == '\'')
			sub_extract_the_phrase(dst, src, &i, &j);
		else
			dst[j++] = src[i++];
	}
	dst[j] = 0;
	*index = i;
}
