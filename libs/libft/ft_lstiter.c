/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <vivan-de@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 08:39:14 by victor            #+#    #+#             */
/*   Updated: 2021/09/02 19:06:51 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*i;

	if (lst == NULL)
		return ;
	i = lst;
	while (i->next != NULL)
	{
		f(i->content);
		i = i->next;
	}
	f(i->content);
}
