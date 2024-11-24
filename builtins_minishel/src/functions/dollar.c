/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:44:26 by surpetro          #+#    #+#             */
/*   Updated: 2024/11/24 21:47:04 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishel.h"


char	*variable(char *str)
{
	int		i;
	int		l;
	int		buff;
	char	*res;

	i = 0;
	l = 0;
	if(str[i] == '$')
	{
		i++;
		if(str[i] >= '0' && str[i] <= '9')
			i++;
		return str;
	}
	buff = i;
	while (str[buff])
		buff++;
	res = malloc(sizeof(char *) * buff + 1);
	if(!res)
		return  (NULL);
	while (str[i])
		res[l++] = str[i++];
	res[l] = '\0';
	
	return (res);
}

char	*remains(char *key)
{
	char	*str;

	int	i;
	int	l;
	int	len;

	i = 1;
	l = 0;
	while (key[i])
	{
		if(key[i] == '$')
			break;
		if (key[i] && ((key[i] >= 'a' && key[i] <= 'z')
			|| (key[i] >= 'A' && key[i] <= 'Z')
			|| (key[i] >= '0' && key[i] <= '9') || key[i] == '_'))
			i++;
		else
			break;
	}
	len = ft_strlen(&key[i]);
	str = malloc(sizeof(char *) * len + 1);
	while (key[i])
	{
		if(key[i] == '$')
			break;
		str[l++] = key[i++];
	}
	str[l] = '\0';
	return str;
}

int	valid_remains_line(char *str)
{
	if (((str[0] >= 'a' && str[0] <= 'z')
		|| (str[0] >= 'A' && str[0] <= 'Z')
		|| (str[0] >= '0' && str[0] <= '9') || str[0] == '_'))
		return 0;
	return (1);
}

char	*open_dollar(char *key, t_duplicate_env *duplicate_env)
{
	int		i;
	int		value_len;
	char	*res_buff = NULL;
	char	*res_line = NULL;
	char	*res_line_remains = NULL;
	char	*buff;
	t_duplicate_env *start = duplicate_env;

	i = 0;
	while (key[i])
	{
		value_len = 0;
		if(key[i] == '$' && key[i + 1] > 32)
		{
			i++;
			buff = ft_strndup(&key[i]);
			buff = ft_strtrim(buff, " ");
			if (dollar_validation(buff) == 0)
			{
				free(buff);
				break;
			}
			while (duplicate_env)
			{
				if (ft_strcmp(buff, duplicate_env->key) == 0)
				{
					value_len = ft_strlen(duplicate_env->value);
					res_buff = malloc(sizeof(char *) * value_len);
					if (!res_buff)
						return NULL;
					res_buff = ft_strdup(duplicate_env->value); 
				}
				duplicate_env = duplicate_env->next;
			}
			duplicate_env = start->next;
			res_line_remains = remains(&key[i]);
			res_line = ft_strjoin(res_line, res_buff);
			if (valid_remains_line(res_line_remains) == 1)
			{
				res_line = ft_strjoin(res_line, res_line_remains);
				free(res_line_remains);
			}
		}
		else if(key[i] == '$')
			res_line = ft_strjoin(res_line, "$");
		i++;
	}
	return res_line;
}

char	*dollar_func(char *str, utils_t *utils)
{
	int		i = 0;
	int		count = 0;
	char	*s1_before = NULL;
	char	*s2_key = NULL;
	char	*s3_after = NULL;
	char	*res_line_key = NULL;
	char	*res_1 = NULL;
	char	*resultant = NULL;

	while (str[i] && str[i] <= 32)
		i++;
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
			s2_key = key(str);
			s3_after = after(str);
		}
		if (count > 0 && str[i] != '$')
		{
			s1_before = before_dollar(str);
			s2_key = key(str);
			s3_after = after(str);
		}
		else
		{
			s1_before = before_dollar(str);
			return s1_before;
		}	
	}
	else
		return (NULL);
	if (ft_strcmp(s1_before, "\0") == 0)
		s1_before = completion_status(str, utils->last_exit_status);
	res_line_key = open_dollar(s2_key, utils->shell->duplicate_env);
	res_1 = ft_strjoin(s1_before, res_line_key);
	resultant = ft_strjoin(res_1, s3_after);
	return resultant;
}