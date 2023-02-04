/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_try_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/04 19:40:31 by victor.simo      ###   ########.fr       */
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
		exit(0);
	else if (is_equal(line, "echo", 4))
		ft_printf("%s\n", line + 5);
	return (0);
}

BOOL	cmd_try_run(t_ctx **ctx, char *line)
{
	char *trimmed;

	errno = 0;
	trimmed = ft_strtrim(line, " ");
	if (is_builtin(trimmed))
		cmd_run_builtin(ctx, trimmed);
	else if (cmd_is_valid(trimmed))
		cmd_exec(trimmed, (*ctx)->env);
	else
		errno = 127;
	if (errno != EXIT_SUCCESS)
		ft_printf("minishell: %s: %s\n", trimmed, strerror(errno));
	free(trimmed);
	return (1);
}