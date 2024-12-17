/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:57:25 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/10 18:26:40 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishel.h"

int	part_function_checking_variable(t_duplicate_env *last,
	char *buff, char *buff_key, char *buff_vlaue)
{
	int	exists;

	exists = 0;
	while (last)
	{
		if (ft_strcmp(buff, last->key) == 0)
		{
			exists = 1;
			if (last->type == 0)
			{
				last->type = 1;
				if (last->value != NULL)
					free(last->value);
				last->value = NULL;
			}
			else if (validation_equal_variable(buff_key) == 1)
			{
				if (last->value != NULL)
					free(last->value);
				last->value = ft_strdup(buff_vlaue);
			}
		}
		last = last->next;
	}
	return (exists);
}

int	checking_existence_variable(t_duplicate_env *env,
	char *buff_key, char *buff_vlaue, int exists)
{
	t_duplicate_env	*last;
	int				len;
	char			*buff;

	last = env;
	len = find_equal(buff_key);
	buff = ft_substr(buff_key, 0, len);
	exists = part_function_checking_variable(last, buff, buff_key, buff_vlaue);
	free(buff);
	return (exists);
}

void	print_export_list(t_utils *utils)
{
	t_export	*start_exp;

	start_exp = utils->shell->input_export;
	while (utils->shell->input_export)
	{
		if (utils->shell->input_export->type == 1)
		{
			if (utils->shell->input_export->value
				&& utils->shell->input_export->value[0])
			{
				printf("declare -x %s=", utils->shell->input_export->key);
				printf("\"%s\"\n", utils->shell->input_export->value);
			}
			else if (utils->shell->input_export->value == NULL)
				printf("declare -x %s\n", utils->shell->input_export->key);
			else
				printf("declare -x %s=\"\"\n", utils->shell->input_export->key);
		}
		utils->shell->input_export = utils->shell->input_export->next;
	}
	utils->shell->input_export = start_exp;
}

/*------------------------the part where
		the env is added to the export------------------------*/
static t_export	*create_export_node(t_duplicate_env *dup_env)
{
	t_export	*new_node;

	new_node = malloc(sizeof(t_export));
	if (new_node == NULL)
		return (NULL);
	new_node->type = dup_env->type;
	new_node->key = ft_strdup(dup_env->key);
	if (dup_env->value != NULL)
		new_node->value = ft_strdup(dup_env->value);
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	add_enviorment(t_shell *shell)
{
	t_duplicate_env	*start;
	t_export		*iter;
	t_export		start1;

	start = shell->duplicate_env;
	iter = &start1;
	while (shell->duplicate_env)
	{
		iter->next = create_export_node(shell->duplicate_env);
		if (iter->next == NULL)
			break ;
		iter = iter->next;
		shell->duplicate_env = shell->duplicate_env->next;
	}
	iter->next = NULL;
	shell->duplicate_env = start;
	shell->input_export = start1.next;
}
