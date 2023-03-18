/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lkd_lst_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:44:37 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/28 07:27:22 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int			validate_args(t_lkd_lst **list);

t_lkd_lst	*lkd_lst_map(t_lkd_lst **list, t_lkd_lst_map_fn fn)
{
	t_lkd_lst		*new_list;
	t_lkd_node		*current_lkd_node;
	unsigned int	i;
	void			*content;

	if (!validate_args(list))
		return (NULL);
	new_list = lkd_lst_new_list();
	current_lkd_node = (*list)->head;
	if (!new_list)
		return (NULL);
	i = 0;
	while (i++ < (*list)->size)
	{
		content = fn(current_lkd_node->content, i - 1);
		lkd_lst_add_back(&new_list, lkd_lst_new_node(content));
		current_lkd_node = current_lkd_node->next;
	}
	return (new_list);
}
