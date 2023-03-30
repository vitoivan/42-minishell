/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/30 08:11:16 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	*init_pids(void)
{
	int	i;
	int	*pids;
	int	max_pids;

	max_pids = MAX_PIDS;
	pids = ft_calloc(max_pids, sizeof(int));
	i = 0;
	while (i < max_pids)
	{
		pids[i] = -1;
		i++;
	}
	return (pids);
}

t_ctx	*ctx_init(int argc, char **argv, char **envp)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)ft_calloc(1, sizeof(t_ctx));
	ctx->env = ctx_parse_env(envp);
	ctx->user = getenv("USER");
	ctx->path = getcwd(ctx->path, PATH_SIZE);
	ctx->hostname = get_hostname(envp);
	ctx->argc = argc;
	ctx->argv = argv;
	ctx->buffer = ft_calloc(PIPE_BUFFER, sizeof(char));
	ctx->pid = -1;
	ctx->pids = init_pids();
	return (ctx);
}
