/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:57:25 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/04 22:32:51 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishel.h"
t_duplicate_env	*create_new_node(char *key, char *value, int type)
{
	t_duplicate_env	*new_node;

	new_node = malloc(sizeof(t_duplicate_env));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

int	process_string(char *str, t_var_export *var)
{
	var->buff_key = ft_substr(str, 0, var->findel);
	var->buff_vlaue = ft_substr(str, ft_strlen(var->buff_key), ft_strlen(str));
	if (validation_symble_variable(var->buff_key) == 0)
		return (0);
	return (1);
}

void	add_to_list(t_duplicate_env **env,
	t_duplicate_env **last, t_duplicate_env *node)
{
	if (*last)
		(*last)->next = node;
	else
		*env = node;
	*last = node;
}

void	handle_logic(t_var_export *var, t_duplicate_env **env,
	t_duplicate_env **last)
{
	int	len_equally;

	len_equally = ft_strlen(var->buff_key) - 1;
	if (checking_existence_variable(*env, var->buff_key, var->buff_vlaue) == 0)
	{
		if (validation_equal_variable(var->buff_key) == 1)
		{
			if (var->buff_vlaue && var->buff_vlaue[0])
				var->new_node = create_new_node(ft_substr
						(var->buff_key, 0, var->findel - 1),
						ft_strdup(var->buff_vlaue), 1);
			else if (var->buff_key[len_equally] == '=')
				var->new_node = create_new_node(ft_substr
						(var->buff_key, 0, var->findel - 1),
						"", 1);
			else
				var->new_node = create_new_node(ft_substr
						(var->buff_key, 0, var->findel - 1),
						NULL, 1);
		}
		else
		{
			var->new_node = create_new_node(ft_substr
					(var->buff_key, 0, var->findel),
					NULL, 1);
		}
		add_to_list(env, last, var->new_node);
	}
}

int	arr_string_element(char *str, t_duplicate_env **env,
	t_duplicate_env **last)
{
	t_var_export	var;

	var.buff_key = NULL;
	var.buff_vlaue = NULL;
	var.findel = find_before_equal(str);
	if (var.findel == 0)
		return (0);
	if (process_string(str, &var) == 0)
		return (0);
	handle_logic(&var, env, last);
	// system("leaks minishell");
	free_export(var);
	return (1);
}
