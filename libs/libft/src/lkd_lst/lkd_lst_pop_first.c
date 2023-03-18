/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lkd_lst_pop_first.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:44:37 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/28 07:27:37 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		validate_args(t_lkd_lst **list);
void	__lkd_lst_del_node(t_lkd_lst **list, t_lkd_node *node,
			t_lkd_lst_del_node_fn fn);

void	lkd_lst_pop_first(t_lkd_lst **list, t_lkd_lst_del_node_fn fn)
{
	t_lkd_node	*current_lkd_node;
	t_lkd_node	*next_lkd_node;

	if (!validate_args(list))
		return ;
	current_lkd_node = (*list)->head;
	if (!current_lkd_node)
		return ;
	next_lkd_node = current_lkd_node->next;
	__lkd_lst_del_node(list, current_lkd_node, fn);
	if ((*list)->size > 1 && next_lkd_node)
	{
		(*list)->head = next_lkd_node;
		(*list)->tail->next = next_lkd_node;
		(*list)->head->prev = (*list)->tail;
	}
}
