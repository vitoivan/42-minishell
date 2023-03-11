/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/10 19:18:08 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_equal(char *s1, char *s2, int len)
{
	return (ft_strncmp(s1, s2, len) == 0);
}

void	builtin_main(t_ctx **ctx, char *line)
{
	if (is_equal(line, "pwd", 3))
		pwd(ctx, line);
	else if (is_equal(line, "clear", 5))
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
		echo(ctx, line);
	else if (is_equal(line, "env", 3))
		env(ctx);
	else if (is_equal(line, "unset", 5))
		unset(ctx, line);
}
