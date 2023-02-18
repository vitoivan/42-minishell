

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_with_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/05 15:27:26 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ctx_populate_buffer(t_ctx **ctx, char *data)
{
	int		i;
	char	*buffer;

	if (!data)
		return ;
	i = -1;
	ft_bzero((*ctx)->buffer, PIPE_BUFFER);
	buffer = (*ctx)->buffer;
	while (data[++i])
		buffer[i] = data[i];
}
