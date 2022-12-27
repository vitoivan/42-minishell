/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_terminal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2022/12/27 09:19:36 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_terminal(t_ctx *ctx)
{
	char	*user_and_host;
	char	*tmp;

	tmp = ft_strjoin(ctx->user, "@");
	user_and_host = ft_strjoin(tmp, ctx->hostname);
	free(tmp);
	ft_printf(COLOR_BOLD GREEN "%s" WHT ":" BLU "%s" WHT "$ " RESET_COLOR REMOVE_BOLD,
				user_and_host,
				ctx->path);
	free(user_and_host);
}
