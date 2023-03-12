/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/12 16:24:14 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_ctx	*ctx;

	line = NULL;
	ctx = ctx_init(argc, argv, envp);
	while (True)
	{
		ft_bzero(ctx->buffer, PIPE_BUFFER);
		if (!get_line_from_terminal(&line, ctx) || !line)
			return (1);
		if (line[0] == '\0' || line[0] == '\n')
		{
			free_if_exists((void **)&line);
			continue ;
		}
		ctx->root_cmd = ft_parser(&ctx, line);
		free_if_exists((void **)&line);
		if (ctx->root_cmd)
		{
			exec_tree(ctx->root_cmd, &ctx);
			// ft_printf("%s", ctx->buffer);
			ft_putstr_fd(ctx->buffer, STDERR_FILENO);
			ft_bzero(ctx->buffer, PIPE_BUFFER);
			ast_node_free(ctx->root_cmd);
		}
	}
	return (0);
}
