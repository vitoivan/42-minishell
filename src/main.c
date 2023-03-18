/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/18 11:19:47 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ctx	*g_ctx;

static void	clear(void)
{
	ft_putstr_fd(g_ctx->buffer, STDOUT_FILENO);
	ft_bzero(g_ctx->buffer, PIPE_BUFFER);
	ast_node_free(g_ctx->root_cmd);
}

static int	handle_empty_line(char **line)
{
	if (!line || !*line)
		return (-1);
	if ((*line)[0] == '\0' || (*line)[0] == '\n')
	{
		free_if_exists((void **)line);
		return (-1);
	}
	return (1);
}

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
		if (handle_empty_line(&line) == -1)
			continue ;
		g_ctx->root_cmd = ft_parser(&g_ctx, line);
		free_if_exists((void **)&line);
		if (g_ctx->root_cmd)
		{
			exec_tree(g_ctx->root_cmd, &g_ctx);
			clear();
		}
	}
	return (0);
}
