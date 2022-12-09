/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <vivan-de@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 23:52:07 by victor            #+#    #+#             */
/*   Updated: 2021/09/06 10:39:13 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list *lst, t_node *new)
{
  if ( !lst || !new )
      return ;
	if (lst->tail == NULL)
    lst->head = lst->tail = new;
	else
	{
    lst->tail->next = new; 
    lst->tail = new;
	}
  lst->size++;
}
