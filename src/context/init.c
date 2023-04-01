/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/04/01 11:33:53 by victor.simo      ###   ########.fr       */
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

static char	**parse_lkd_lst_to_vector(t_ctx **ctx)
{
	char		**envp;
	t_lkd_node	*tmp;
	int			i;
	int			size;

	size = (*ctx)->env->size;
	envp = (char **)ft_calloc(size + 1, sizeof(char *));
	i = 0;
	tmp = (*ctx)->env->head;
	while (i < size)
	{
		tmp = tmp->next;
		envp[i] = (char *)tmp->content;
		i++;
	}
	return (envp);
}

t_ctx	*ctx_init(int argc, char **argv, char **envp)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)ft_calloc(1, sizeof(t_ctx));
	ctx->env = ctx_parse_env(envp);
	ctx->env_vector = parse_lkd_lst_to_vector(&ctx);
	ctx->user = getenv("USER");
	ctx->path = getcwd(ctx->path, PATH_SIZE);
	ctx->hostname = get_hostname(envp);
	ctx->argc = argc;
	ctx->argv = argv;
	ctx->pid = -1;
	ctx->pids = init_pids();
	return (ctx);
}
