/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lkd_lst_add_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:44:37 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/28 07:27:08 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	lkd_lst_add_front(t_lkd_lst **list, t_lkd_node *node)
{
	if (!list || !node)
		return ;
	if (!*list)
		return ;
	if ((*list)->head == NULL)
	{
		(*list)->head = node;
		(*list)->tail = node;
	}
	else
	{
		node->next = (*list)->head;
		node->prev = (*list)->tail;
		(*list)->tail->next = node;
		(*list)->head->prev = node;
		(*list)->head = node;
	}
	(*list)->size++;
}
