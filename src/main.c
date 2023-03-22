/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/22 11:16:11 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_ctx		*g_ctx;

static void	clear(void)
{
	ft_putstr_fd(g_ctx->buffer, STDOUT_FILENO);
	ft_bzero(g_ctx->buffer, PIPE_BUFFER);
	ast_node_free(g_ctx->root_cmd);
	lkd_lst_kill_list(&g_ctx->cmdlist, del_token_list);
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

static int	is_redir(t_token_type type)
{
	if (type == TOKEN_OPERATOR_PIPE)
		return (True);
	if (type == TOKEN_OPERATOR_REDIRECT)
		return (True);
	if (type == TOKEN_OPERATOR_REDIRECT_APPEND)
		return (True);
	if (type == TOKEN_OPERATOR_REDIRECT_INPUT)
		return (True);
	if (type == TOKEN_OPERATOR_HERE_DOC)
		return (True);
	return (False);
}

static void	create_pipes(t_lkd_lst *list)
{
	t_lkd_node		*cur;
	t_lkd_node		*next;
	t_lkd_node		*prev;
	t_token			*token;
	unsigned int	i;
	unsigned int	max_pipes;
	int				**pipes;
	int				fileout;
	char			*trimmed;
	int				filein;

	max_pipes = list->size;
	pipes = (int **)malloc(sizeof(int *) * max_pipes);
	i = 0;
	while (i < max_pipes)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		pipes[i][0] = -1;
		pipes[i][1] = -1;
		i++;
	}
	i = 0;
	cur = list->head;
	next = NULL;
	prev = NULL;
	while (cur && i < list->size && cur->content)
	{
		token = (t_token *)cur->content;
		if (token->type == TOKEN_ERROR)
		{
			ft_putstr_fd("LexerError: Token with error\n", STDERR_FILENO);
			exit(1);
		}
		if (cur->prev && i > 0)
			prev = cur->prev;
		if (cur->next && i < list->size - 1)
			next = cur->next;
		if (is_redir(token->type))
		{
			// caso o node atual seja um pipe,
			if (token->type == TOKEN_OPERATOR_PIPE)
			{
				if (pipe(pipes[i]) == -1)
				{
					ft_putstr_fd("Error creating pipe\n", STDERR_FILENO);
					exit(1);
				}
				if (prev)
					((t_token *)prev->content)->fileout = pipes[i][1];
				if (next)
					((t_token *)next->content)->filein = pipes[i][0];
			}
			// caso o node atual seja um redirecionamento,
			if (token->type == TOKEN_OPERATOR_REDIRECT
				|| token->type == TOKEN_OPERATOR_REDIRECT_APPEND)
			{
				// se o node anterior for um comando,
				// setar o fileout do node anterior
				if (next && ((t_token *)next->content)->type != TOKEN_COMMAND)
				{
					ft_putstr_fd("Error: no command after redirect\n",
									STDERR_FILENO);
					exit(1);
				}
				trimmed = ft_strtrim(((t_token *)next->content)->start,
										" ");
				fileout = 1;
				if (token->type == TOKEN_OPERATOR_REDIRECT)
					fileout = open(trimmed, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				else if (token->type == TOKEN_OPERATOR_REDIRECT_APPEND)
					fileout = open(trimmed, O_WRONLY | O_CREAT | O_APPEND,
							0644);
				if (fileout == -1)
				{
					ft_putstr_fd(trimmed, STDERR_FILENO);
					ft_putstr_fd(": ", STDERR_FILENO);
					ft_putstr_fd("error opening file\n", STDERR_FILENO);
					free(trimmed);
					exit(1);
				}
				free(trimmed);
				if (prev && ((t_token *)prev->content)->type == TOKEN_COMMAND)
					((t_token *)prev->content)->fileout = fileout;
				// se o node seguinte for um comando,
				//	setar o filein do node seguinte
			}
			if (token->type == TOKEN_OPERATOR_REDIRECT_INPUT)
			{
				if (prev && ((t_token *)prev->content)->type != TOKEN_COMMAND)
				{
					ft_putstr_fd("Error: no command before redirect\n",
									STDERR_FILENO);
					exit(1);
				}
				trimmed = ft_strtrim(((t_token *)next->content)->start,
										" ");
				filein = open(trimmed, O_RDONLY);
				if (filein == -1)
				{
					ft_putstr_fd(trimmed, STDERR_FILENO);
					ft_putstr_fd(": ", STDERR_FILENO);
					ft_putstr_fd("error opening file\n", STDERR_FILENO);
					free(trimmed);
					exit(1);
				}
				free(trimmed);
				if (prev && ((t_token *)prev->content)->type == TOKEN_COMMAND)
					((t_token *)prev->content)->filein = filein;
			}
		}
		cur = cur->next;
		i++;
	}
	i = 0;
	while (i < max_pipes)
	{
		if (pipes[i])
			free(pipes[i]);
		i++;
	}
	free(pipes);
}

static void	close_pipes(t_lkd_lst *list)
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

static int	need_skip_cmd(t_lkd_node *node)
{
	t_token		*token;
	t_token		*tmp_token;
	t_lkd_node	*prev;
	t_lkd_node	*next;

	prev = NULL;
	next = NULL;
	if (!node)
		return (0);
	token = (t_token *)node->content;
	if (!token)
		return (0);
	if (node->prev)
		prev = node->prev;
	if (node->next)
		next = node->next;
	if (prev && prev->content != NULL)
	{
		tmp_token = (t_token *)prev->content;
		if (token->type == TOKEN_COMMAND)
		{
			if (!tmp_token)
				return (0);
			if (tmp_token->type == TOKEN_OPERATOR_REDIRECT)
				return (1);
			if (tmp_token->type == TOKEN_OPERATOR_REDIRECT_INPUT)
				return (1);
			if (tmp_token->type == TOKEN_OPERATOR_REDIRECT_APPEND)
				return (1);
		}
	}
	return (0);
}

static void	exec_cmds(t_lkd_lst *list)
{
	unsigned int	i;
	t_lkd_node		*cur;
	t_lkd_node		*prev;
	t_lkd_node		*next;
	t_token			*token;
	char			**args;
	char			*trimmed;
	char			*binary_path;
	char			*cmd;
	int				max_pids;
	char			**env;

	i = 0;
	cur = list->head;
	max_pids = list->size;
	next = NULL;
	prev = NULL;
	while (cur && i < list->size && cur->content)
	{
		token = (t_token *)cur->content;
		if (!token)
			break ;
		if (i > 0)
			prev = cur->prev;
		if (i < list->size - 1)
			next = cur->next;
		if (prev && need_skip_cmd(cur) == True)
		{
			cur = cur->next;
			i++;
			continue ;
		}
		if (token->type == TOKEN_COMMAND)
		{
			cmd = get_cmd_from_line(token->start);
			trimmed = ft_strtrim(cmd, " ");
			free(cmd);
			if (is_builtin(trimmed))
			{
				free(trimmed);
				builtin_main(&g_ctx, token->start, token);
			}
			else if (cmd_is_valid(token->start))
			{
				binary_path = get_cmd_binary_path(trimmed);
				cmd_get_args(&args, token->start);
				g_ctx->pids[i] = fork();
				if (g_ctx->pids[i] == 0)
				{
					dup2(token->filein, STDIN_FILENO);
					dup2(token->fileout, STDOUT_FILENO);
					close_pipes(list);
					env = parse_ldk_lst_to_char_array(g_ctx->env);
					execve(binary_path, args, env);
					ft_putstr_fd(trimmed, STDERR_FILENO);
					ft_putstr_fd(": ", STDERR_FILENO);
					ft_putstr_fd("Error executing command\n", STDERR_FILENO);
					free(trimmed);
					ctx_free(&g_ctx);
					free(binary_path);
					clear_splitted(&args);
					clear_splitted(&env);
					exit(1);
				}
				else
				{
					free(binary_path);
					free(trimmed);
					clear_splitted(&args);
					if (token->filein != STDIN_FILENO)
						close(token->filein);
					if (token->fileout != STDOUT_FILENO)
						close(token->fileout);
				}
			}
			else
			{
				ft_putstr_fd(trimmed, STDERR_FILENO);
				ft_putstr_fd(":  error: command not found\n", STDERR_FILENO);
				free(trimmed);
			}
		}
		cur = cur->next;
		i++;
	}
}

static void	waitpids(void)
{
	unsigned int	i;
	unsigned int	max_pids;

	max_pids = 250;
	i = 0;
	while (i < max_pids)
	{
		if (g_ctx->pids[i] != -1)
			waitpid(g_ctx->pids[i], &g_ctx->status_code, 0);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_lkd_lst	*list;

	line = NULL;
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
		list = g_ctx->cmdlist;
		if (list)
		{
			create_pipes(list);
			exec_cmds(list);
			close_pipes(list);
			waitpids();
		}
		clear();
	}
	return (0);
}
