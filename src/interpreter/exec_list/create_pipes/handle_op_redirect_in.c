/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_op_redirect_in.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:40:24 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/30 03:45:59 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

void	handle_op_redirect_in(t_handle_exec_list *s)
{
	char	*filename;

	if (s->token->type == TOKEN_OPERATOR_REDIRECT_INPUT)
	{
		if (s->prev && ((t_token *)s->prev->content)->type != TOKEN_COMMAND)
		{
			ft_putstr_fd("Error: no command before redirect\n", STDERR_FILENO);
			exit(1);
		}
		filename = ft_strtrim(((t_token *)s->next->content)->start, " \"'\t");
		s->filein = open(filename, O_RDONLY);
		if (s->filein == -1)
		{
			ft_putstr_fd(filename, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd("error opening file\n", STDERR_FILENO);
			free(filename);
			exit(1);
		}
		free(filename);
		if (s->prev && ((t_token *)s->prev->content)->type == TOKEN_COMMAND)
			((t_token *)s->prev->content)->filein = s->filein;
	}
}
