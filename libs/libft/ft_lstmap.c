/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <vivan-de@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 09:42:13 by victor            #+#    #+#             */
/*   Updated: 2021/09/02 19:07:01 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*kill_lst(t_list *lst, void (*del)(void *))
{
	t_list	*tmp;

	tmp = lst;
	while (lst->next != NULL)
	{
		tmp = lst;
		lst = lst->next;
		if (del != NULL)
			del(tmp->content);
		free(tmp);
	}
	if (del != NULL)
		del(tmp->content);
	free(lst);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*i;
	t_list	*new_lst;
	t_list	*head;

	if (lst == NULL || f == NULL)
		return (NULL);
	i = lst;
	head = NULL;
	while (i->next != NULL)
	{
		new_lst = ft_lstnew(f(i->content));
		if (new_lst == NULL)
			return (kill_lst(head, del));
		ft_lstadd_back(&head, new_lst);
		i = i->next;
	}
	new_lst = ft_lstnew(f(i->content));
	if (new_lst == NULL)
		return (kill_lst(head, del));
	ft_lstadd_back(&head, new_lst);
	return (head);
}
