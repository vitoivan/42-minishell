/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <vivan-de@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 10:36:15 by victor            #+#    #+#             */
/*   Updated: 2021/09/06 07:13:09 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list *lst, void (*del)(void*))
{
	t_node	*node;
	t_node	*tmp;

  tmp = NULL;
	if (!lst)
		return ;
	node = lst->head;
	while (node != NULL)
	{
		tmp = node;
    del(node->content);
		node = node->next;
		free(tmp);
	}
}
