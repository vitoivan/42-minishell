/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2022/12/26 16:22:21 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipe_close_read(int pipefd[2])
{
	close(pipefd[0]);
}

void	pipe_close_write(int pipefd[2])
{
	close(pipefd[1]);
}

void	pipe_close_both(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}
