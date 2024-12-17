/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:44:26 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/10 14:50:34 by ayeganya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishel.h"

void	exit_status_dollar(t_var_dollar *var, int last_exit_status,
		char *temp, char *key)
{
	char	*remaining;

	remaining = NULL;
	remaining = remaining_after(key);
	if (!remaining)
		return ;
	var->open_exit_status = opn_ext_sts(last_exit_status);
	temp = ft_strjoin(var->res_line, var->open_exit_status);
	var->res_line = ft_strjoin(temp, remaining);
	free(remaining);
	free(temp);
	temp = 0;
	free(var->open_exit_status);
}

int	search_find_open(t_duplicate_env *duplicate_env,
		t_var_dollar *var, char *temp, char *key)
{
	if (take_key(key, var) == 1)
		return (1);
	env_list_key_search(&duplicate_env, var);
	var->res_line_remains = remains(key);
	if (duplicate_env != NULL)
		temp = ft_strjoin(var->res_line, var->res_buff);
	if (valid_remains_line(var->res_line_remains) == 1)
	{
		var->res_line = ft_strjoin(temp, var->res_line_remains);
		if (temp != NULL)
		{
			free(temp);
			temp = NULL;
		}
		free(var->res_buff);
		free(var->res_line_remains);
	}
	return (0);
}

char	*open_dollar(char *key,
	t_duplicate_env *duplicate_env, t_var_dollar var, int last_exit_status)
{
	t_duplicate_env	*start;
	int				i;
	char			*temp;

	i = -1;
	temp = 0;
	start = duplicate_env;
	while (key[++i])
	{
		if (key[i] == '$' && key[i + 1] == '?')
			exit_status_dollar(&var, last_exit_status, temp, &key[i]);
		else if (key[i] == '$' && key[i + 1] > 32 && key[i + 1] != '$')
		{
			i++;
			if (search_find_open(duplicate_env, &var, temp, &key[i]) == 1)
				break ;
			duplicate_env = start->next;
		}
		else if (key[i] == '$')
			var.res_line = ft_strjoin(var.res_line, "$");
	}
	return (var.res_line);
}

char	*dollar_func_1(char *str, t_utils *utils)
{
	t_var_dollar	var;
	char			*resultant;

	resultant = NULL;
	initialization(&var);
	if (str)
	{
		if (share_dollar_input(&var, str) != NULL)
			return (var.s1_before);
	}
	else
		return (NULL);
	var.res_line_key = open_dollar(var.s2_key,
			utils->shell->duplicate_env, var, utils->last_exit_status);
	var.res_1 = ft_strjoin(var.s1_before, var.res_line_key);
	resultant = ft_strjoin(var.res_1, var.s3_after);
	if (search_for_a_negative_character(resultant) == 1)
		resultant = development_s3_atfer(resultant);
	free_dollar(var);
	return (resultant);
}
