/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_op_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:40:24 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/30 03:45:35 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void	attach_pipe_to_cmd(t_handle_exec_list *s)
{
	t_token	*tmp;

	if (s->prev)
	{
		if (s->i > 2)
		{
			s->tmp_token = (t_token *)s->prev->prev->content;
			tmp = (t_token *)s->prev->prev->prev->content;
			if (s->tmp_token->type == TOKEN_OPERATOR_REDIRECT_INPUT)
				tmp->fileout = s->pipes[s->i][1];
			else if (s->tmp_token->type == TOKEN_OPERATOR_HERE_DOC)
				tmp->fileout = s->pipes[s->i][1];
			else if (((t_token *)s->prev->content)->type == TOKEN_COMMAND)
				((t_token *)s->prev->content)->fileout = s->pipes[s->i][1];
		}
		else if (((t_token *)s->prev->content)->type == TOKEN_COMMAND)
			((t_token *)s->prev->content)->fileout = s->pipes[s->i][1];
	}
	if (s->next && ((t_token *)s->next->content)->type == TOKEN_COMMAND)
		((t_token *)s->next->content)->filein = s->pipes[s->i][0];
}

void	handle_op_pipe(t_handle_exec_list *s)
{
	if (s->token->type == TOKEN_OPERATOR_PIPE)
	{
		if (pipe(s->pipes[s->i]) == -1)
		{
			ft_putstr_fd("Error creating pipe\n", STDERR_FILENO);
			exit(1);
		}
		attach_pipe_to_cmd(s);
	}
}
