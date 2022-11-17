/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <vivan-de@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 23:20:50 by victor            #+#    #+#             */
/*   Updated: 2021/09/16 08:01:01 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*i;
	int		counter;

	if (lst == NULL)
		return (0);
	counter = 0;
	i = lst;
	while (i->next != NULL)
	{
		counter++;
		i = i->next;
	}
	counter++;
	return (counter);
}
