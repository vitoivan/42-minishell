/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lkd_lst_foreach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:44:37 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/18 11:01:15 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int		validate_args(t_lkd_lst **list);

void	lkd_lst_foreach(t_lkd_lst **list, t_lkd_lst_each_fn fn)
{
	t_lkd_node		*current_lkd_node;
	unsigned int	i;

	if (!validate_args(list))
		return ;
	current_lkd_node = (*list)->head;
	i = 0;
	while (i++ < (*list)->size)
	{
		fn(current_lkd_node->content, i - 1);
		current_lkd_node = current_lkd_node->next;
	}
}
