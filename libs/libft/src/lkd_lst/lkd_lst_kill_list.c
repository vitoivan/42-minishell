/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lkd_lst_kill_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:44:37 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/28 07:27:19 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void		__lkd_lst_del_node(t_lkd_lst **list, t_lkd_node *node,
				t_lkd_lst_del_node_fn fn);

static int	validate_args(t_lkd_lst **list)
{
	if (!list)
		return (0);
	if (!*list)
		return (0);
	return (1);
}

void	lkd_lst_kill_list(t_lkd_lst **list, t_lkd_lst_del_node_fn fn)
{
	t_lkd_node	*current_lkd_node;
	t_lkd_node	*next_lkd_node;

	if (!validate_args(list))
		return ;
	current_lkd_node = (*list)->head;
	if ((*list)->size && (*list)->head && (*list)->tail)
	{
		(*list)->tail->next = NULL;
		(*list)->head->prev = NULL;
		while ((*list)->size)
		{
			next_lkd_node = current_lkd_node->next;
			__lkd_lst_del_node(list, current_lkd_node, fn);
			if (next_lkd_node)
			{
				current_lkd_node = next_lkd_node;
				if (next_lkd_node->next)
					next_lkd_node = next_lkd_node->next;
			}
		}
	}
	free(*list);
	*list = NULL;
}
