/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2022/12/31 08:28:18 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ctx	*ctx_init(void)
{
	t_ctx	*ctx;

	ctx = (t_ctx *)ft_calloc(1, sizeof(t_ctx));
	ctx->user = getenv("USERNAME");
	ctx->path = getcwd(ctx->path, PATH_SIZE);
	ctx->hostname = get_hostname();
	return (ctx);
}
