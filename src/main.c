/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/19 08:35:33 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ctx		*g_ctx;

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

static void	waitpids(t_ctx **ctx)
{
	int		status;
	pid_t	pid;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < (*ctx)->pipe_list_i)
	{
		if ((*ctx)->pipe_list[j][0] != -1)
			close((*ctx)->pipe_list[j][0]);
		if ((*ctx)->pipe_list[j][1] != -1)
			close((*ctx)->pipe_list[j][0]);
		j++;
	}
	while (i < (*ctx)->pid_list_i)
	{
		status = 0;
		pid = waitpid((*ctx)->pid_list[i], &status, 0);
		if (WIFEXITED(status))
			(*ctx)->status_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			(*ctx)->status_code = WTERMSIG(status) + 128;
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	line = NULL;
	g_ctx = ctx_init(argc, argv, envp);
	handle_signals();
	signal(SIGQUIT, SIG_IGN);
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
			exec_tree(g_ctx->root_cmd, &g_ctx, False);
			waitpids(&g_ctx);
			clear();
		}
	}
	return (0);
}
