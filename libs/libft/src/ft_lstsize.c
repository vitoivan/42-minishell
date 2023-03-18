/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 23:20:50 by victor            #+#    #+#             */
/*   Updated: 2022/12/09 20:02:36 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
