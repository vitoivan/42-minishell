/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/12 15:01:51 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(t_ctx **ctx)
{
	unsigned int	i;
	t_lkd_node		*node;
	char			buffer[PIPE_BUFFER];
	char			*content;
	int				buff_idx;

	i = -1;
	buff_idx = 0;
	node = (*ctx)->env->head;
	while (++i < (*ctx)->env->size)
	{
		content = ft_strjoin((char *)node->content, "\n");
		if (content)
		{
			ft_strlcpy(&buffer[buff_idx], content, ft_strlen(content) + 1);
			buff_idx += ft_strlen(content);
			node = node->next;
			free(content);
		}
	}
	ctx_populate_buffer(ctx, buffer);
}
