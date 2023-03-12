/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/12 14:28:30 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ctx	*ctx_init(int argc, char **argv, char **envp)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)ft_calloc(1, sizeof(t_ctx));
	ctx->user = getenv("USERNAME");
	ctx->path = getcwd(ctx->path, PATH_SIZE);
	ctx->hostname = get_hostname(envp);
	ctx->argc = argc;
	ctx->argv = argv;
	ctx->env = ctx_parse_env(envp);
	ctx->root_cmd = NULL;
	ctx->buffer = ft_calloc(PIPE_BUFFER, sizeof(char));
	return (ctx);
}
