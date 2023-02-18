/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/18 15:36:44 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_ctx **ctx)
{
	char	*current_path;
	char	*fmt;
	char	*buffer;

	buffer = (*ctx)->buffer;
	current_path = NULL;
	current_path = getcwd(current_path, PATH_SIZE);
	fmt = ft_strjoin(current_path, "\n");
	ctx_populate_buffer(ctx, fmt);
	free(fmt);
	free(current_path);
}
