/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/19 08:20:03 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(t_ctx **ctx)
{
	unsigned int	i;
	t_lkd_node		*node;
	int				buff_idx;

	i = -1;
	buff_idx = 0;
	node = (*ctx)->env->head;
	while (++i < (*ctx)->env->size)
	{
		ft_printf("%s\n", (char *)node->content);
		node = node->next;
	}
}
