/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_try_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/19 08:43:53 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

BOOL	cmd_try_run(t_ctx **ctx, char *line, int in_pipe)
{
	int	pid;
	int	status_code;

	pid = -1;
	status_code = 0;
	(*ctx)->status_code = status_code;
	if (is_builtin(line))
		builtin_main(ctx, line);
	else if (cmd_is_valid(line))
	{
		if (in_pipe == False)
			pid = fork();
		if (pid == 0)
		{
			handle_signals();
			cmd_exec(line, ctx);
		}
		else
		{
			if (pid != -1)
				waitpid(pid, &status_code, 0);
			else
				cmd_exec(line, ctx);
		}
	}
	else
		status_code = 127;
	if (status_code != EXIT_SUCCESS)
		print_errno(ctx, line, status_code);
	(*ctx)->status_code = status_code;
	return (1);
}
