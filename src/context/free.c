/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/19 17:36:24 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ctx_free(t_ctx **ctx)
{
	if (!ctx || !*ctx)
		return ;
	if ((*ctx)->pids != NULL)
		free((*ctx)->pids);
	free_if_exists((void **)&(*ctx)->hostname);
	free_if_exists((void **)&(*ctx)->path);
	free_if_exists((void **)&(*ctx)->buffer);
	lkd_lst_kill_list(&(*ctx)->env, free);
	lkd_lst_kill_list(&(*ctx)->cmdlist, del_token_list);
	if ((*ctx)->root_cmd)
		ast_node_free((*ctx)->root_cmd);
	clear_history();
	free_if_exists((void **)ctx);
}
