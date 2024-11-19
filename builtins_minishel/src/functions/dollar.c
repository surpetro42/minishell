/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:44:26 by surpetro          #+#    #+#             */
/*   Updated: 2024/11/19 00:31:50 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishel.h"

void	free_dollar(char *s)
{
	free(s);
}

char	*before_dollar(char *str)
{
	int		i;
	int		l;
	char	*s;

	i = 0;
	l = 0;
	while (str && str[i] && str[i] != '$')
		i++;
	s = malloc(sizeof(char *) * i + 1);
	if (!s)
		return (NULL);
	while (str[l] && str[l] != '$')
	{
		s[l] = str[l];
		l++;
	}
	if (l == i)
		s[l] = '\0';
	return (s);
}

char	*key(char *str)
{
	int		i;
	int		l;
	int		x;
	char	*s;

	i = 0;
	l = 0;
	x = 0;
	while (str[l] && str[l])
		l++;
	while (l > 0 && str[l] != '$')
		l--;
	while (str[l] && str[l] > 32)
		l++;
	while (str[i] && str[i] != '$')
		i++;
	x = l - i;
	s = malloc(sizeof(char *) * x + 1);
	while (i < l)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*after(char *str)
{
	int		i;
	int		l;
	int		after_len;
	int		buff;
	char	*s;

	i = 0;
	l = 0;
	after_len = 0;
	while (str && str[i])
		i++;
	while (i > 0)
	{
		if (str[i] == '$')
			break ;
		i--;
	}
	while (str && str[i] > 32)
		i++;
	buff = i;
	while (str[i++])
		after_len++;
	s = malloc(sizeof(char *) * after_len);
	if (!s)
		return (NULL);
	while (str[buff])
		s[l++] = str[buff++];
	s[l] = '\0';
	return (s);
}

int	dollar_validation(char *s)
{
	int	i;

	i = 0;
	if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
		|| (s[i] >= '0' && s[i] <= '9') || s[i] == '_' )
	{
		i++;
		while (s[i])
		{
			if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
				|| (s[i] >= '0' && s[i] <= '9') || s[i] == '_'))
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

char	*search_key(t_duplicate_env *duplicate_env, char *s)
{
	char *str;
	int i = 0;

	if(s[i] >= '0' && s[i] <= '9')
		i++;
	if (s[i] >= '0' && s[i] <= '9')
		return &s[++i];
	while (duplicate_env->next)
	{
		if (ft_strcmp(&s[i], duplicate_env->key) == 0)
		{
			str = ft_strdup(duplicate_env->value);
			return (str);
		}
		else if (ft_strcmp(&s[i], "$") == 0)
			return (s);
		duplicate_env = duplicate_env->next;
	}
	return NULL;
}

char	*variable(char *str)
{
	int i = 0;
	int l = 0;
	char	*res;
	if(str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i])
		i++;
	res = malloc(sizeof(char *) *i + 1);
	i = 0;
	while (str[++i])
		res[l++] = str[i];
	res[l] = '\0';
	return (res);
}

char	*open_dollar(char *key, t_duplicate_env *duplicate_env)
{
	int		i;
	int		value_len;
	char	*res_buff;
	char	*res_line = NULL;
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
			res_line = ft_strjoin(res_line, res_buff);
			res_line = ft_strjoin(res_line, " ");
			if (res_buff)
			{
				free(res_buff);
				free(buff);
			}
		}
		else if(key[i] == '$')
		{
			res_line = ft_strjoin(res_line, "$");
		}
		i++;
	}
	return res_line;
}

char	*completion_status(char *str, int last_exit_status)
{
	char	*s;

	s = NULL;
	if(str[0] == '$' && str[1] == '?')
		s = ft_itoa(last_exit_status);
	return s;
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
	free_dollar(s1_before);
	free_dollar(s2_key);
	free_dollar(s3_after);
	free_dollar(res_1);
	free_dollar(res_line_key);
	return resultant;
}
