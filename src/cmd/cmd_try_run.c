/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_try_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/11 19:01:03 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

BOOL	cmd_try_run(t_ctx **ctx, char *line)
{
	errno = 0;
	(*ctx)->status_code = 0;
	if (is_builtin(line))
		builtin_main(ctx, line);
	else if (cmd_is_valid(line))
		cmd_exec(line, ctx);
	else
		errno = 127;
	(*ctx)->status_code = errno;
	if (errno != EXIT_SUCCESS)
	{
		print_errno(line);
		ft_bzero((*ctx)->buffer, PIPE_BUFFER);
	}
	return (1);
}
