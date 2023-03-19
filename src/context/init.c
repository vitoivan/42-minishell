/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/19 06:48:36 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_lists(t_ctx **ctx)
{
	int	i;

	i = 0;
	(*ctx)->pid_list = (int *)ft_calloc(PID_LIST_SIZE, sizeof(int));
	while (i < PID_LIST_SIZE)
	{
		(*ctx)->pid_list[i] = -1;
		i++;
	}
	i = 0;
	(*ctx)->pipe_list = (int **)ft_calloc(PIPE_LIST_SIZE, sizeof(int *));
	while (i < PIPE_LIST_SIZE)
	{
		(*ctx)->pipe_list[i] = (int *)ft_calloc(2, sizeof(int));
		(*ctx)->pipe_list[i][0] = -1;
		(*ctx)->pipe_list[i][1] = -1;
		i++;
	}
}

t_ctx	*ctx_init(int argc, char **argv, char **envp)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)ft_calloc(1, sizeof(t_ctx));
	ctx->user = getenv("USER");
	ctx->path = getcwd(ctx->path, PATH_SIZE);
	ctx->hostname = get_hostname(envp);
	ctx->argc = argc;
	ctx->argv = argv;
	ctx->env = ctx_parse_env(envp);
	ctx->root_cmd = NULL;
	ctx->buffer = ft_calloc(PIPE_BUFFER, sizeof(char));
	ctx->pid = -1;
	init_lists(&ctx);
	ctx->pid_list_i = 0;
	ctx->pipe_list_i = 0;
	return (ctx);
}
