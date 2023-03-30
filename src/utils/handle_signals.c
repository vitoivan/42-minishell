/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:44:41 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/28 10:04:10 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	send_sig_to_processes(int sig)
{
	int	i;
	int	done;

	done = 0;
	i = 0;
	while (i < MAX_PIDS)
	{
		if (g_ctx->pids[i] != -1)
		{
			done = 1;
			kill(g_ctx->pids[i], sig);
			g_ctx->pids[i] = -1;
		}
		i++;
	}
	return (done);
}

static void	handle_sigint(int sig)
{
	int	done;

	(void)sig;
	done = send_sig_to_processes(SIGINT);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (!done)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_ctx->status_code = 130;
}

static void	handle_sigquit(int sig)
{
	int	done;

	(void)sig;
	done = send_sig_to_processes(SIGQUIT);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (!done)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_ctx->status_code = 131;
}

void	handle_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}
