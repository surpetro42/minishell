/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:44:26 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/05 01:49:12 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishel.h"



int	search_for_a_negative_character(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if(s[i] < 0)
			return (1);
		i++;
	}
	return (0);
}

char	*development_s3_atfer(char *str)
{
	int		i;
	int		l;
	int		len;
	char	*buff;

	i = 0;
	l = 0;
	len = ft_strlen(str);
	buff = malloc(sizeof(char *) * len + 1);
	if (!buff)
		return (NULL);
	while (str[i])
	{
		if(str[i] < 0)
			i++;
		buff[l] = str[i];
		if (str[i])
			i++;
		l++;
	}
	buff[i] = '\0';
	free(str);
	return (buff);
}

char	*open_dollar(char *key, t_duplicate_env *duplicate_env, t_var_dollar var, int i)
{
	t_duplicate_env *start;

	start = duplicate_env;
	while (key[++i])
	{
		if (key[i] == '$' && key[i + 1] > 32)
		{
			i++;
			if (take_key(key, i, &var) == 1)
				break;
			env_list_key_search(&duplicate_env, &var);
			var.res_line_remains = remains(&key[i]);
			if (duplicate_env != NULL)
				var.res_line = ft_strjoin(var.res_line, var.res_buff);
			if (valid_remains_line(var.res_line_remains) == 1)
			{
				var.res_line = ft_strjoin(var.res_line, var.res_line_remains);
				free(var.res_line_remains);
			}
			duplicate_env = start->next;
		}
		else if(key[i] == '$')
			var.res_line = ft_strjoin(var.res_line, "$");
	}
	return (var.res_line);
}

// void	split_into_parts()
// {}

char	*dollar_func(char *str, utils_t *utils)
{
	int				i = 0;
	int				count = 0;
	char			*resultant = NULL;
	t_var_dollar	var;

	initialization(&var);
	while (str[i] && str[i] <= 32)
		i++;
	// split_into_parts();
	if (str)
	{
		while (str[i])
		{
			if (str[i] == '$')
				count++;
			i++;
		}
		if (str[i] == '$')
		{
			var.s2_key = key(str);
			var.s3_after = after(str);
		}
		if (count > 0 && str[i] != '$')
		{
			var.s1_before = before_dollar(str);
			var.s2_key = key(str);
			var.s3_after = after(str);
		}
		else
		{
			var.s1_before = before_dollar(str);
			return (var.s1_before);
		}	
	}
	else
		return (NULL);
	if (ft_strcmp(var.s1_before, "\0") == 0)
		var.s1_before = completion_status(str, utils->last_exit_status);
	var.res_line_key = open_dollar(var.s2_key, utils->shell->duplicate_env, var, -1);
	var.res_1 = ft_strjoin(var.s1_before, var.res_line_key);
	resultant = ft_strjoin(var.res_1, var.s3_after);
	if(search_for_a_negative_character(resultant) == 1)
		resultant = development_s3_atfer(resultant);
	return resultant;
}