/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_try_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/20 14:59:40 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

BOOL	cmd_try_run(t_ctx **ctx, char *line)
{
	errno = 0;
	if (is_builtin(line))
		builtin_main(ctx, line);
	else if (cmd_is_valid(line))
		cmd_exec(line, ctx);
	else
		errno = 127;
	if (errno != EXIT_SUCCESS)
	{
		print_errno(line);
		ft_bzero((*ctx)->buffer, PIPE_BUFFER);
	}
	return (1);
}
