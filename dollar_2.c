/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayeganya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:56:43 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/10 14:59:58 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int	count_the_key_size(t_dfs *dfs)
{
	int	i;
	int	size;

	i = dfs->i;
	size = 0;
	if (dfs->src[i] == '?')
	{
		size = 1;
		i++;
	}
	else
	{
		while ((dfs->src[i] >= '0' && dfs->src[i] <= '9') || (dfs->src[i] >= \
				'A' && dfs->src[i] <= 'Z') || (dfs->src[i] >= 'a' \
					&& dfs->src[i] <= 'z') || dfs->src[i] == '_')
		{
			size++;
			i++;
		}
	}
	return (size);
}

int	extract_key(t_dfs *dfs, char **key)
{
	int	size;

	dfs->i++;
	size = count_the_key_size(dfs);
	if (size == 0)
		return (1);
	*key = (char *)malloc(sizeof(char) * (size + 1));
	if (*key == 0)
		return (-1);
	ft_strlcpy(*key, &(dfs->src[dfs->i]), size + 1);
	dfs->i += size;
	return (0);
}

int	find_the_value(t_utils *utils, char **value, char *key)
{
	t_duplicate_env	*dup_env;

	*value = 0;
	dup_env = utils->shell->duplicate_env;
	while (dup_env)
	{
		if (dup_env->type == 1 && ft_strcmp(key, dup_env->key) == 0)
		{
			*value = dup_env->value;
			return (0);
		}
		dup_env = dup_env->next;
	}
	return (1);
}

int	ex_status_value(t_utils *utils, char **value)
{
	int	i;
	int	s;

	*value = (char *)malloc(22);
	if (*value == 0)
		return (1);
	i = 0;
	s = utils->last_exit_status;
	while (s > 9)
	{
		s /= 10;
		i++;
	}
	(*value)[i + 1] = 0;
	s = utils->last_exit_status;
	while (s > 9)
	{
		(*value)[i] = s % 10 + '0';
		s /= 10;
		i--;
	}
	(*value)[0] = s + '0';
	return (0);
}
