/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:40:24 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/30 20:18:07 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void	init_struct(t_lkd_lst *list, t_handle_exec_list *s)
{
	s->i = 0;
	s->cur = list->head;
	s->list = list;
	s->prev = NULL;
	s->next = NULL;
	s->token = NULL;
	s->tmp_token = NULL;
	s->filein = STDIN_FILENO;
	s->fileout = STDOUT_FILENO;
}

static void	run_child_process(char *cmd, char *binary_path, char **args,
		t_handle_exec_list *s)
{
	char	**env;

	dup2(s->token->filein, STDIN_FILENO);
	dup2(s->token->fileout, STDOUT_FILENO);
	close_pipes(s->list);
	env = parse_ldk_lst_to_char_array(g_ctx->env);
	execve(binary_path, args, env);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("Error executing command\n", STDERR_FILENO);
	free(cmd);
	ctx_free(&g_ctx);
	free(binary_path);
	clear_splitted(&args);
	clear_splitted(&env);
	exit(1);
}

static void	exec_binary(char *cmd, t_handle_exec_list *s)
{
	char	*binary_path;
	char	**args;

	binary_path = get_cmd_binary_path(cmd);
	cmd_get_args(&args, s->token->start);
	g_ctx->pids[s->i] = fork();
	if (g_ctx->pids[s->i] == 0)
		run_child_process(cmd, binary_path, args, s);
	else
	{
		free(binary_path);
		free(cmd);
		clear_splitted(&args);
		if (s->token->filein != STDIN_FILENO)
			close(s->token->filein);
		if (s->token->fileout != STDOUT_FILENO)
			close(s->token->fileout);
	}
}

static void	handle_token_cmd(t_handle_exec_list *s)
{
	char	*cmd;
	char	*trimmed;

	if (s->token->type == TOKEN_COMMAND)
	{
		cmd = get_cmd_from_line(s->token->start);
		trimmed = ft_strtrim(cmd, " \t\v\f\r");
		free(cmd);
		g_ctx->status_code = 0;
		if (is_builtin(trimmed))
		{
			free(trimmed);
			builtin_main(&g_ctx, s->token->start, s->token);
		}
		else if (cmd_is_valid(s->token->start))
			exec_binary(trimmed, s);
		else
		{
			ft_putstr_fd(trimmed, STDERR_FILENO);
			ft_putstr_fd(":  error: command not found\n", STDERR_FILENO);
			g_ctx->status_code = 127;
			free(trimmed);
		}
	}
}

void	exec_cmds(t_lkd_lst *list)
{
	t_handle_exec_list	s;

	init_struct(list, &s);
	while (s.cur && (unsigned int)s.i < list->size && s.cur->content)
	{
		s.token = (t_token *)s.cur->content;
		if (!s.token)
			break ;
		if (s.i > 0)
			s.prev = s.cur->prev;
		if ((unsigned int)s.i < list->size - 1)
			s.next = s.cur->next;
		if (s.prev && need_skip_cmd(s.cur) == True)
		{
			s.cur = s.cur->next;
			s.i++;
			continue ;
		}
		else
			handle_token_cmd(&s);
		s.cur = s.cur->next;
		s.i++;
	}
}
