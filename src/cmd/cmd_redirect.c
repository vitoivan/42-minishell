/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/16 15:30:24 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cmd_redirect_input(char *filepath, t_ctx **ctx);

void	cmd_redirect(char *filepath, int mode, t_ctx **ctx)
{
	int	fileout;

	if (mode == NODE_REDIRECT_APPEND)
		fileout = open(filepath, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (mode == NODE_REDIRECT)
		fileout = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == NODE_REDIRECT_INPUT)
	{
		cmd_redirect_input(filepath, ctx);
		return ;
	}
	else
		fileout = -1;
	if (fileout == -1)
	{
		ft_putstr_fd(strerror((*ctx)->status_code), STDERR_FILENO);
		return ;
	}
	ft_putstr_fd((*ctx)->buffer, fileout);
	close(fileout);
	ft_bzero((*ctx)->buffer, PIPE_BUFFER);
}

static void	cmd_redirect_input(char *filepath, t_ctx **ctx)
{
	int	filein;

	filein = open(filepath, O_RDONLY);
	if (filein == -1)
	{
		ft_putstr_fd(strerror((*ctx)->status_code), STDERR_FILENO);
		return ;
	}
	ft_bzero((*ctx)->buffer, PIPE_BUFFER);
	read(filein, (*ctx)->buffer, PIPE_BUFFER);
	close(filein);
}
