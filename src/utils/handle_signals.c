/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:44:41 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/19 08:48:45 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	kill_ctx(int sig)
{
	int	i;

	i = 0;
	while (i < PID_LIST_SIZE)
	{
		if (g_ctx->pid_list[i] != -1)
			kill(g_ctx->pid_list[i], sig);
		g_ctx->pid_list[i] = -1;
		i++;
	}
}

static void	handle_sigint(int sig)
{
	int	i;

	i = 0;
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		ctx_free(&g_ctx);
		exit(1);
	}
	g_ctx->pid = -1;
	g_ctx->status_code = 130;
}

static void	handle_sigquit(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
	kill_ctx(SIGQUIT);
	g_ctx->pid = -1;
	g_ctx->status_code = 131;
}

void	handle_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
