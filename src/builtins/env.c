/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/22 13:44:51 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(t_ctx **ctx, t_token *token)
{
	unsigned int	i;
	t_lkd_node		*node;
	char			*content;

	i = -1;
	node = (*ctx)->env->head;
	while (++i < (*ctx)->env->size)
	{
		content = ft_strjoin((char *)node->content, "\n");
		if (content)
		{
			ft_putstr_fd(content, token->fileout);
			free(content);
		}
		node = node->next;
	}
}
