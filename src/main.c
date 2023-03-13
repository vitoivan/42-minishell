/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/12 20:09:05 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	line = NULL;
	g_ctx = ctx_init(argc, argv, envp);
	handle_signals();
	while (True)
	{
		ft_bzero(g_ctx->buffer, PIPE_BUFFER);
		if (!get_line_from_terminal(&line, g_ctx) || !line)
			return (1);
		if (line[0] == '\0' || line[0] == '\n')
		{
			free_if_exists((void **)&line);
			continue ;
		}
		g_ctx->root_cmd = ft_parser(&g_ctx, line);
		free_if_exists((void **)&line);
		if (g_ctx->root_cmd)
		{
			exec_tree(g_ctx->root_cmd, &g_ctx);
			// ft_printf("%s", ctx->buffer);
			ft_putstr_fd(g_ctx->buffer, STDOUT_FILENO);
			ft_bzero(g_ctx->buffer, PIPE_BUFFER);
			ast_node_free(g_ctx->root_cmd);
		}
	}
	return (0);
}
