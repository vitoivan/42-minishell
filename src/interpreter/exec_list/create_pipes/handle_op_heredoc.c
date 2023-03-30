/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_op_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:40:24 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/30 03:48:36 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	handle_op_heredoc(t_handle_exec_list *s)
{
	if (s->token->type == TOKEN_OPERATOR_HERE_DOC)
	{
		if (s->prev && ((t_token *)s->prev->content)->type == TOKEN_COMMAND)
		{
			s->filein = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (s->filein == -1)
			{
				ft_putstr_fd("error while running heredoc\n", STDERR_FILENO);
				exit(1);
			}
			ft_putstr_fd(((t_token *)s->next->content)->start, s->filein);
			ft_putstr_fd("\n", s->filein);
			close(s->filein);
			s->filein = open("here_doc", O_RDONLY);
			((t_token *)s->prev->content)->filein = s->filein;
		}
	}
}
