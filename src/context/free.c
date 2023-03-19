/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/19 06:50:13 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	del_env_node(void *node)
{
	free(node);
}

void	ctx_free(t_ctx **ctx)
{
	int	i;

	free_if_exists((void **)&(*ctx)->hostname);
	free_if_exists((void **)&(*ctx)->path);
	free_if_exists((void **)&(*ctx)->buffer);
	free_if_exists((void **)&(*ctx)->pid_list);
	i = 0;
	while (i < PIPE_LIST_SIZE)
	{
		free_if_exists((void **)&(*ctx)->pipe_list[i]);
		i++;
	}
	free_if_exists((void **)&(*ctx)->pipe_list);
	lkd_lst_kill_list(&(*ctx)->env, del_env_node);
	if ((*ctx)->root_cmd)
		ast_node_free((*ctx)->root_cmd);
	free_if_exists((void **)ctx);
	clear_history();
}
