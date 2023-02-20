/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/20 12:33:26 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	del_env_node(void *node)
{
	free(node);
}

void	ctx_free(t_ctx **ctx)
{
	free_if_exists((void **)&(*ctx)->hostname);
	free_if_exists((void **)&(*ctx)->path);
	free_if_exists((void **)&(*ctx)->buffer);
	lkd_lst_kill_list(&(*ctx)->env, del_env_node);
	if ((*ctx)->root_cmd)
		ast_node_free((*ctx)->root_cmd);
	free_if_exists((void **)ctx);
}
