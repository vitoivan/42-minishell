/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:40:24 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/30 08:09:46 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void	del_pipes(int **pipes, unsigned int max_pipes)
{
	unsigned int	i;

	i = 0;
	while (i < max_pipes)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

int	is_redir(t_token_type type)
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

static void	handle_operators(t_handle_exec_list *s)
{
	handle_op_pipe(s);
	handle_op_redirect_out(s);
	handle_op_redirect_in(s);
	handle_op_heredoc(s);
}

static void	create_pipe(t_lkd_node *cur, int **pipes, unsigned int i)
{
	t_token				*token;
	t_handle_exec_list	*s;

	token = (t_token *)cur->content;
	s = (t_handle_exec_list *)ft_calloc(1, sizeof(t_handle_exec_list));
	s->cur = cur;
	s->pipes = pipes;
	s->i = i;
	s->token = token;
	if (token->type == TOKEN_ERROR)
	{
		ft_putstr_fd("LexerError: Token with error\n", STDERR_FILENO);
		exit(1);
	}
	if (cur->prev && i > 0)
		s->prev = s->cur->prev;
	if (cur->next && i < g_ctx->cmdlist->size - 1)
		s->next = s->cur->next;
	if (is_redir(token->type))
		handle_operators(s);
	free(s);
}

void	create_pipes(t_lkd_lst *list)
{
	t_lkd_node		*cur;
	unsigned int	i;
	unsigned int	max_pipes;
	int				**pipes;

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
	while (cur && i < list->size && cur->content)
	{
		create_pipe(cur, pipes, i);
		cur = cur->next;
		i++;
	}
	del_pipes(pipes, max_pipes);
}
