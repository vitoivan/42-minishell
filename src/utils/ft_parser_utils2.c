/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:16:59 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/27 22:48:03 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node_type	get_node_type(t_token *token)
{
	if (token->type == TOKEN_OPERATOR_AND)
		return (NODE_AND);
	if (token->type == TOKEN_OPERATOR_OR)
		return (NODE_OR);
	if (token->type == TOKEN_OPERATOR_PIPE)
		return (NODE_PIPE);
	if (token->type == TOKEN_OPERATOR_REDIRECT_INPUT)
		return (NODE_REDIRECT_INPUT);
	if (token->type == TOKEN_OPERATOR_HERE_DOC)
		return (NODE_HERE_DOCUMENT);
	if (token->type == TOKEN_OPERATOR_HERE_ARGS)
		return (NODE_HERE_ARGS);
	if (token->type == TOKEN_OPERATOR_REDIRECT)
		return (NODE_REDIRECT);
	if (token->type == TOKEN_OPERATOR_REDIRECT_APPEND)
		return (NODE_REDIRECT_APPEND);
	if (token->type == TOKEN_OPERATOR_SEMICOLON)
		return (NODE_SEMICOLON);
	if (token->type == TOKEN_ERROR)
		return (NODE_INVALID);
	return (NODE_COMMAND);
}
