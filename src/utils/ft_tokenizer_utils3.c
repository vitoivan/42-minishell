/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer_utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:19:25 by jv                #+#    #+#             */
/*   Updated: 2023/03/18 09:55:00 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*lexer_next_token(t_ctx **ctx, t_lexer *lexer, BYTE is_here_doc)
{
	t_token	*new_current_token;

	skip_white_spaces(lexer);
	if (is_here_doc)
		new_current_token = scan_here_document(lexer);
	else
	{
		new_current_token = scan_command(ctx, lexer);
		if (!new_current_token)
			new_current_token = scan_operator(ctx, lexer);
		if (!new_current_token)
			return (NULL);
	}
	return (new_current_token);
}

void	del_token(t_token *token)
{
	if (token != NULL)
	{
		free(token->start);
		free(token);
	}
}

void	advance_to_next_token(t_ctx **ctx, t_parser_context *context)
{
	context->parser.previus_token = context->parser.current_token;
	if (get_previus_token(context)
		&& get_previus_token(context)->type == TOKEN_OPERATOR_HERE_DOC)
		context->parser.current_token = lexer_next_token(ctx, &context->lexer,
				1);
	else
		context->parser.current_token = lexer_next_token(ctx, &context->lexer,
				0);
	context->lexer.start = context->lexer.current_position;
}