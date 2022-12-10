/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lkd_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2022/12/10 16:09:09 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_fn(void *data, t_uint ind)
{
	ft_printf("{ ind: %d, string: %s }, ", ind, (char *)data);
}

void	print_lkd_list(t_lkd_lst **list)
{
	ft_printf("[ ");
	lkd_lst_foreach(list, print_fn);
	ft_printf("]");
}
