/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/20 11:27:30 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_redirect(char *filepath, int mode, t_ctx **ctx)
{
	int	fileout;

	if (mode == NODE_REDIRECT_APPEND)
		fileout = open(filepath, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (mode == NODE_REDIRECT)
		fileout = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fileout = -1;
	if (fileout == -1)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return ;
	}
	ft_putstr_fd((*ctx)->buffer, fileout);
	close(fileout);
	ft_bzero((*ctx)->buffer, PIPE_BUFFER);
}
