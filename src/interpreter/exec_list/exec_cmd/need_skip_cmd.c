/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   need_skip_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:40:24 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/30 08:23:12 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

static int	validate_redirects(t_token *token, t_lkd_node *prev)
{
	t_token		*tmp_token;

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
	return (-1);
}

int	need_skip_cmd(t_lkd_node *node)
{
	t_token		*token;
	t_lkd_node	*prev;

	prev = NULL;
	if (!node)
		return (0);
	token = (t_token *)node->content;
	if (!token)
		return (0);
	if (node->prev)
		prev = node->prev;
	if (prev && prev->content != NULL)
	{
		if (validate_redirects(token, prev) != -1)
			return (validate_redirects(token, prev) != -1);
	}
	if (token->type == TOKEN_OPERATOR_HERE_ARGS)
		return (1);
	return (0);
}
