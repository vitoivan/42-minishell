/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/30 08:18:11 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ctx		*g_ctx;

static int	handle_empty_line(char **line)
{
	int	i;

	i = 0;
	if (!line || !*line)
		return (-1);
	if (ft_strlen(*line) == 0)
		return (-1);
	while ((*line)[i] && ((*line)[i] == ' ' || (*line)[i] == '\n'))
		i++;
	if ((*line)[i] == '\0')
	{
		free_if_exists((void **)line);
		return (-1);
	}
	return (1);
}

void	close_pipes(t_lkd_lst *list)
{
	unsigned int	i;
	t_lkd_node		*cur;
	t_token			*token;

	i = 0;
	cur = list->head;
	while (cur && i <= list->size && cur->content)
	{
		token = (t_token *)cur->content;
		if (!token)
			break ;
		if (token->filein != STDIN_FILENO)
			close(token->filein);
		if (token->fileout != STDOUT_FILENO)
			close(token->fileout);
		cur = cur->next;
		i++;
	}
}

static void	waitpids(void)
{
	unsigned int	i;

	i = 0;
	while (i < MAX_PIDS)
	{
		if (g_ctx->pids[i] != -1)
		{
			waitpid(g_ctx->pids[i], &g_ctx->status_code, 0);
			g_ctx->pids[i] = -1;
		}
		i++;
	}
	unlink("here_doc");
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	g_ctx = ctx_init(argc, argv, envp);
	g_ctx->hostname = get_hostname(envp);
	handle_signals();
	while (True)
	{
		if (!get_line_from_terminal(&line, g_ctx) || !line)
			return (1);
		if (handle_empty_line(&line) == -1)
			continue ;
		g_ctx->cmdlist = (t_lkd_lst *)ft_parser(&g_ctx, line);
		free_if_exists((void **)&line);
		if (g_ctx->cmdlist)
		{
			create_pipes(g_ctx->cmdlist);
			exec_cmds(g_ctx->cmdlist);
			close_pipes(g_ctx->cmdlist);
			waitpids();
		}
	}
	return (0);
}
