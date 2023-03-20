/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:44:41 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/19 16:19:08 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_sigint(int sig)
{
	unsigned int	i;
	t_lkd_lst		*list;
	t_lkd_node		*node;
	t_token			*token;

	(void)sig;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	i = 0;
	list = g_ctx->cmdlist;
	if (!list || !list->head)
		return ;
	node = list->head;
	while (i < list->size)
	{
		token = (t_token *)node->content;
		if (!token)
			break ;
		if (token->type == TOKEN_COMMAND)
		{
			if (g_ctx->pids[i] != -1)
				kill(g_ctx->pids[i], SIGINT);
			g_ctx->pids[i] = -1;
		}
		i++;
	}
	g_ctx->status_code = 130;
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
