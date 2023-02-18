/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_try_run.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/18 17:13:43 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_equal(char *s1, char *s2, int n)
{
	return (!ft_strncmp(s1, s2, n));
}

static int	cmd_run_builtin(t_ctx **ctx, char *line)
{
	char	*data_fmt;

	if (is_equal(line, "pwd", 3))
		pwd(ctx);
	else if (is_equal(line, "clear", 4))
		ctx_populate_buffer(ctx, "\e[1;1H\e[2J");
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
	{
		data_fmt = ft_strjoin(line + 5, "\n");
		ctx_populate_buffer(ctx, data_fmt);
		free(data_fmt);
	}
	return (0);
}

static void	print_errno(char *line)
{
	char	*cmd;

	cmd = get_cmd_from_line(line);
	if (errno == 127)
		ft_printf("%s: command not found\n", line);
	else if (!cmd_is_valid(cmd))
		ft_printf("%s: %s\n", line, strerror(errno));
	free(cmd);
}

BOOL	cmd_try_run(t_ctx **ctx, char *line)
{
	errno = 0;
	if (is_builtin(line))
		cmd_run_builtin(ctx, line);
	else if (cmd_is_valid(line))
		cmd_exec(line, ctx);
	else
		errno = 127;
	if (errno != EXIT_SUCCESS)
		print_errno(line);
	return (1);
}
