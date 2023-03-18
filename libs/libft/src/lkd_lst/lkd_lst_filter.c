/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lkd_lst_filter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:44:37 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/28 07:28:08 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int			validate_args(t_lkd_lst **list);

t_lkd_lst	*lkd_lst_filter(t_lkd_lst **list, t_lkd_lst_filter_fn fn)
{
	t_lkd_lst		*new_list;
	t_lkd_node		*current_lkd_node;
	unsigned int	i;
	int				filter_result;

	if (!validate_args(list))
		return (NULL);
	new_list = lkd_lst_new_list();
	current_lkd_node = (*list)->head;
	if (!new_list)
		return (NULL);
	i = 0;
	while (i++ < (*list)->size)
	{
		filter_result = fn(current_lkd_node->content, i - 1);
		if (filter_result)
			lkd_lst_add_back(&new_list,
				lkd_lst_new_node(current_lkd_node->content));
		current_lkd_node = current_lkd_node->next;
	}
	return (new_list);
}
