/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/04/01 11:34:35 by victor.simo      ###   ########.fr       */
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
	free((*ctx)->env_vector);
	lkd_lst_kill_list(&(*ctx)->env, free);
	lkd_lst_kill_list(&(*ctx)->cmdlist, del_token_list);
	clear_history();
	free_if_exists((void **)ctx);
}
