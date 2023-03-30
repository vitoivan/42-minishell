/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_op_redirect_out.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:40:24 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/30 09:07:28 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static void	attach_fd_to_cmd(t_handle_exec_list *s)
{
	if (s->i > 2 && s->prev)
	{
		s->tmp_token = (t_token *)s->prev->prev->content;
		if (s->tmp_token->type == TOKEN_OPERATOR_REDIRECT_INPUT)
			((t_token *)s->prev->prev->prev->content)->fileout = s->fileout;
		else if (s->tmp_token->type == TOKEN_OPERATOR_HERE_DOC)
			((t_token *)s->prev->prev->prev->content)->fileout = s->fileout;
		else if (((t_token *)s->prev->content)->type == TOKEN_COMMAND)
			((t_token *)s->prev->content)->fileout = s->fileout;
	}
	else if (s->prev && ((t_token *)s->prev->content)->type == TOKEN_COMMAND)
		((t_token *)s->prev->content)->fileout = s->fileout;
}

static void	get_fileout(t_handle_exec_list *s, char *filename)
{
	if (s->token->type == TOKEN_OPERATOR_REDIRECT)
		s->fileout = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (s->token->type == TOKEN_OPERATOR_REDIRECT_APPEND)
		s->fileout = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (s->fileout == -1)
	{
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd("error opening file\n", STDERR_FILENO);
		free(filename);
		exit(1);
	}
	free(filename);
}

void	handle_op_redirect_out(t_handle_exec_list *s)
{
	char	*filename;

	if (s->token->type == TOKEN_OPERATOR_REDIRECT
		|| s->token->type == TOKEN_OPERATOR_REDIRECT_APPEND)
	{
		if (s->next && ((t_token *)s->next->content)->type != TOKEN_COMMAND)
		{
			ft_putstr_fd("Error: no command after redirect\n", STDERR_FILENO);
			exit(1);
		}
		filename = ft_strtrim(((t_token *)s->next->content)->start, " \"'\t");
		s->fileout = 1;
		if (s->token->type == TOKEN_OPERATOR_REDIRECT)
			s->fileout = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (s->token->type == TOKEN_OPERATOR_REDIRECT_APPEND)
			s->fileout = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		get_fileout(s, filename);
		attach_fd_to_cmd(s);
	}
}
