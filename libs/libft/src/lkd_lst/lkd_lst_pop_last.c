/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lkd_lst_pop_last.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:44:37 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/28 07:27:40 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		validate_args(t_lkd_lst **list);
void	__lkd_lst_del_node(t_lkd_lst **list, t_lkd_node *node,
			t_lkd_lst_del_node_fn fn);

void	lkd_lst_pop_last(t_lkd_lst **list, t_lkd_lst_del_node_fn fn)
{
	t_lkd_node	*current_lkd_node;
	t_lkd_node	*prev_node;

	if (!validate_args(list))
		return ;
	current_lkd_node = (*list)->tail;
	if (!current_lkd_node)
		return ;
	prev_node = current_lkd_node->prev;
	__lkd_lst_del_node(list, current_lkd_node, fn);
	if ((*list)->size > 1 && prev_node)
	{
		(*list)->tail = prev_node;
		(*list)->head->prev = prev_node;
		(*list)->tail->next = (*list)->head;
	}
}
