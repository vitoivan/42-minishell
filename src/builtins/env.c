/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/20 12:12:24 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(t_ctx **ctx)
{
	unsigned int	i;
	t_lkd_node		*node;

	i = -1;
	node = (*ctx)->env->head;
	while (++i < (*ctx)->env->size)
	{
		if (node->content)
		{
			ft_printf("%s\n", (char *)node->content);
			node = node->next;
		}
	}
}
