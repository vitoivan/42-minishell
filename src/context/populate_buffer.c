/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/16 15:14:50 by vivan-de         ###   ########.fr       */
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
