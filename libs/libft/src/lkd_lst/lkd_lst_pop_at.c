/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lkd_lst_pop_at.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:44:37 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/28 07:27:34 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int			validate_args(t_lkd_lst **lst);
void		__lkd_lst_del_node(t_lkd_lst **list, t_lkd_node *node,
				t_lkd_lst_del_node_fn fn);

static int	pop_in_extremes(t_lkd_lst **lst, t_uint i, t_lkd_lst_del_node_fn fn)
{
	if (i == 0)
	{
		lkd_lst_pop_first(lst, fn);
		return (1);
	}
	else if (i == (*lst)->size - 1)
	{
		lkd_lst_pop_last(lst, fn);
		return (1);
	}
	return (0);
}

static void	pop_thought_tail(t_lkd_lst **list, t_uint i,
		t_lkd_lst_del_node_fn fn)
{
	t_lkd_node	*current_lkd_node;
	t_lkd_node	*prev;
	t_lkd_node	*next;

	current_lkd_node = (*list)->tail;
	while (i-- > 0)
	{
		if (current_lkd_node)
			current_lkd_node = current_lkd_node->prev;
	}
	if (current_lkd_node && (*list)->size > 2)
	{
		prev = current_lkd_node->prev;
		next = current_lkd_node->next;
		__lkd_lst_del_node(list, current_lkd_node, fn);
		prev->next = next;
		next->prev = prev;
	}
}

static void	pop_thought_head(t_lkd_lst **list, t_uint i,
		t_lkd_lst_del_node_fn fn)
{
	t_lkd_node	*current_lkd_node;
	t_lkd_node	*prev;
	t_lkd_node	*next;

	current_lkd_node = (*list)->head;
	while (i-- > 0)
	{
		if (current_lkd_node)
			current_lkd_node = current_lkd_node->next;
	}
	if (current_lkd_node && (*list)->size > 2)
	{
		prev = current_lkd_node->prev;
		next = current_lkd_node->next;
		__lkd_lst_del_node(list, current_lkd_node, fn);
		prev->next = next;
		next->prev = prev;
	}
}

void	lkd_lst_pop_at(t_lkd_lst **lst, t_uint i, t_lkd_lst_del_node_fn fn)
{
	if (!validate_args(lst))
		return ;
	if (i > (*lst)->size - 1 || i < 0)
		return ;
	if (pop_in_extremes(lst, i, fn))
		return ;
	if (i > (*lst)->size / 2)
		pop_thought_tail(lst, i, fn);
	else
		pop_thought_head(lst, i, fn);
}
