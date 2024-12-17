/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:57:25 by surpetro          #+#    #+#             */
/*   Updated: 2024/12/10 01:06:36 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishel.h"

int	ft_env_elem_size(t_export *begin_list)
{
	int	count;

	count = 0;
	while (begin_list)
	{
		count++;
		begin_list = begin_list->next;
	}
	return (count);
}

t_export	*ft_env_elem_at(t_export *begin_list, unsigned int nbr)
{
	unsigned int	i;

	i = 0;
	while (i < nbr && begin_list->next)
	{
		begin_list = begin_list->next;
		i++;
	}
	if (i != nbr)
		return (NULL);
	return (begin_list);
}

t_export	*ft_merge_sorted_list(t_export *left, t_export *right,
			int (*cmp)())
{
	t_export	dummy;
	t_export	*sorted_list;

	sorted_list = &dummy;
	while (left && right)
	{
		if ((*cmp)(left->key, right->key) < 0)
		{
			sorted_list->next = left;
			left = left->next;
		}
		else
		{
			sorted_list->next = right;
			right = right->next;
		}
		sorted_list = sorted_list->next;
	}
	if (left)
		sorted_list->next = left;
	else if (right)
		sorted_list->next = right;
	return (dummy.next);
}

t_export	*merge_sort(t_export *begin_list, int (*cmp)())
{
	t_export	*left;
	t_export	*right;
	t_export	*pre_right;
	int			list_size;

	list_size = ft_env_elem_size(begin_list);
	if (begin_list == NULL || list_size < 2)
		return (begin_list);
	left = begin_list;
	pre_right = ft_env_elem_at(begin_list, (list_size / 2) - 1);
	right = pre_right->next;
	pre_right->next = NULL;
	left = merge_sort(left, cmp);
	right = merge_sort(right, cmp);
	return (ft_merge_sorted_list(left, right, cmp));
}

void	ft_env_elem_sort(t_export **begin_list, int (*cmp)())
{
	*begin_list = merge_sort(*begin_list, cmp);
}
