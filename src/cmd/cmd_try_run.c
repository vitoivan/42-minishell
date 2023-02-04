/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_try_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/04 20:40:28 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_equal(char *s1, char *s2, int n)
{
	return (!ft_strncmp(s1, s2, n));
}

static int	cmd_run_builtin(t_ctx **ctx, char *line)
{
	if (is_equal(line, "pwd", 3))
		pwd();
	else if (is_equal(line, "clear", 4))
		ft_printf("\e[1;1H\e[2J");
	else if (is_equal(line, "cd", 2))
	{
		cmd_cd(line);
		ctx_update(ctx);
	}
	else if (is_equal(line, "export", 6))
		cmd_export(ctx, line);
	else if (is_equal(line, "exit", 4))
	{
		ctx_free(ctx);
		exit(0);
	}
	else if (is_equal(line, "echo", 4))
		ft_printf("%s\n", line + 5);
	return (0);
}

BOOL	cmd_try_run(t_ctx **ctx, char *line)
{
	errno = 0;
	if (is_builtin(line))
		cmd_run_builtin(ctx, line);
	else if (cmd_is_valid(line))
		cmd_exec(line, (*ctx)->env);
	else
		errno = 127;
	if (errno != EXIT_SUCCESS)
		ft_printf("minishell: %s: %s\n", line, strerror(errno));
	return (1);
}