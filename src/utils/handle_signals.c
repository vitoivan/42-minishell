/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:44:41 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/13 10:10:07 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	if (g_ctx->pid != -1)
	{
		kill(g_ctx->pid, SIGINT);
		g_ctx->pid = -1;
		g_ctx->status_code = 130;
	}
}

static void	handle_sigquit(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	if (g_ctx->pid != -1)
	{
		kill(g_ctx->pid, SIGQUIT);
		g_ctx->pid = -1;
		g_ctx->status_code = 131;
	}
}

void	handle_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
