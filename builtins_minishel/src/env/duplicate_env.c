/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:13:27 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/09 19:53:45 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishel.h"

int	find(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	handle_env_entry(t_duplicate_env *iter, char *env_entry)
{
	int	find_el;

	find_el = find(env_entry);
	iter->next = malloc(sizeof(t_duplicate_env));
	if (!iter->next)
		return ;
	iter->next->type = 1;
	iter->next->key = ft_substr(env_entry, 0, find_el);
	if (!iter->next->key)
	{
		free(iter->next);
		iter->next = NULL;
		return ;
	}
	if (ft_strcmp(iter->next->key, "OLDPWD") != 0)
		iter->next->value = ft_substr(env_entry,
				find_el + 1, ft_strlen(env_entry));
	else
		iter->next->value = NULL;
}

void	process_env_entries(t_duplicate_env *start, char **env)
{
	t_duplicate_env	*iter;
	int				i;

	i = 0;
	iter = start;
	while (env[i])
	{
		handle_env_entry(iter, env[i]);
		if (!iter->next)
			return ;
		iter = iter->next;
		i++;
	}
	iter->next = NULL;
}

void	duplicate_env(t_shell *shell, char **env)
{
	t_duplicate_env	start;

	start.next = NULL;
	process_env_entries(&start, env);
	shell->duplicate_env = start.next;
}
