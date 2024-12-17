/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:04:33 by ayeganya          #+#    #+#             */
/*   Updated: 2024/12/10 19:34:10 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"

int	replace_var_to_value_2(t_dfs *dfs, char *key, char *value)
{
	char	*tmp_str;

	tmp_str = ft_strjoin(dfs->dst, value);
	if (ft_strcmp(key, "?") == 0)
		free(value);
	if (tmp_str == 0)
		return (free(key), 1);
	free(dfs->dst);
	dfs->dst = tmp_str;
	return (free(key), 0);
}

int	replace_var_to_value(t_dfs *dfs, t_utils *utils)
{
	char	*key;
	int		temp;
	char	*value;
	char	*tmp_str;

	temp = extract_key(dfs, &key);
	if (temp == -1)
		return (1);
	if (temp == 1)
	{
		tmp_str = ft_strjoin(dfs->dst, "$");
		free(dfs->dst);
		dfs->dst = tmp_str;
		return (0);
	}
	if (ft_strcmp(key, "?") == 0)
	{
		if (ex_status_value(utils, &value) == 1)
			return (free(key), 0);
	}
	else
		if (find_the_value(utils, &value, key) == 1)
			return (free(key), 0);
	return (replace_var_to_value_2(dfs, key, value));
}

int	extract_str(t_dfs *dfs, char **str)
{
	int		i;
	int		size;
	int		j;

	i = dfs->i;
	size = 0;
	j = 0;
	while (dfs->src[i] && dfs->src[i] != '$')
		if (dfs->src[i++] != -16)
			size++;
	*str = (char *)malloc(sizeof(char) * (size + 1));
	if (*str == 0)
		return (1);
	i = dfs->i;
	while (dfs->src[i] && dfs->src[i] != '$')
	{
		if (dfs->src[i] != -16)
			(*str)[j++] = dfs->src[i++];
		else
			i++;
	}
	(*str)[j] = 0;
	dfs->i = i;
	return (0);
}

int	add_str(t_dfs *dfs)
{
	char	*str;
	char	*tmp;

	extract_str(dfs, &str);
	tmp = ft_strjoin(dfs->dst, str);
	if (tmp == 0)
		return (free(str), 1);
	free(dfs->dst);
	dfs->dst = tmp;
	return (free(str), 0);
}

char	*dollar_func(char *str, t_utils *utils)
{
	t_dfs	dfs;
	char	*result;

	dfs.i = 0;
	dfs.dst = (char *)malloc(sizeof(char));
	(dfs.dst)[0] = 0;
	dfs.src = str;
	while (str[dfs.i])
	{
		if (str[dfs.i] == '$')
		{
			if (replace_var_to_value(&dfs, utils) == 1)
				return (0);
		}
		else
			if (add_str(&dfs) == 1)
				return (0);
	}
	result = (char *)malloc(sizeof(char) * (ft_strlen(dfs.dst) + 1));
	if (result != 0)
		ft_strlcpy(result, dfs.dst, ft_strlen(dfs.dst) + 1);
	free(dfs.dst);
	return (result);
}
