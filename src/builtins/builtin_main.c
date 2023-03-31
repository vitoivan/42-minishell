/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/30 22:22:58 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_equal(char *s1, char *s2, int len)
{
	return (ft_strncmp(s1, s2, len) == 0);
}

void	builtin_main(t_ctx **ctx, char *line, t_token *token)
{
	if (is_equal(line, "pwd", 3))
		pwd(ctx, line, token);
	else if (is_equal(line, "clear", 5))
		ft_putstr_fd("\e[1;1H\e[2J", token->fileout);
	else if (is_equal(line, "cd", 2))
	{
		cmd_cd(ctx, line);
		ctx_update(ctx);
	}
	else if (is_equal(line, "export", 6))
		cmd_export(ctx, line);
	else if (is_equal(line, "exit", 4))
		custom_exit(line, -1);
	else if (is_equal(line, "echo", 4))
		echo(ctx, line, token);
	else if (is_equal(line, "env", 3))
		env(ctx, token);
	else if (is_equal(line, "unset", 5))
		unset(ctx, line);
}
