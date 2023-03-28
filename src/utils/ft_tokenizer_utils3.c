/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer_utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 08:19:25 by jv                #+#    #+#             */
/*   Updated: 2023/03/27 21:04:33 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*lexer_next_token(t_ctx **ctx, t_parser_context *context, BYTE is_here_doc)
{
	t_token	*new_current_token;

	skip_white_spaces(&context->lexer);
	if (is_here_doc)
		new_current_token = scan_here_document(&context->lexer);
	else
	{
		new_current_token = scan_command(ctx, context);
		if (!new_current_token)
			new_current_token = scan_operator(ctx, context);
		if (!new_current_token)
			return (NULL);
	}
	return (new_current_token);
}

void	del_token(t_token *token)
{
	char	**args;
	BYTE 	i;

	i = 0;
	if (token != NULL)
	{
		if (token->type == TOKEN_COMMAND)
		{
			args = token->args - 1;
			while (args[i])
			{
				free(args[i]);
				i++;
			}
			free(args);
		}
		free(token->start);
		free(token);
	}
}

void del_token_list(void *token) 
{
	del_token((t_token *)token);
}

void	advance_to_next_token(t_ctx **ctx, t_parser_context *context)
{
	context->parser.previus_token = context->parser.current_token;
	if (get_previus_token(context)
		&& get_previus_token(context)->type == TOKEN_OPERATOR_HERE_DOC)
		context->parser.current_token = lexer_next_token(ctx, context,
				1);
	else
		context->parser.current_token = lexer_next_token(ctx, context,
				0);

	context->lexer.start = context->lexer.current_position;
}

BYTE	ft_lexer_is_readable(t_lexer *lexer, BYTE *s_quote, BYTE *d_quote)
{
	char curr;
	char prev;

	curr = *lexer->current_position;
	prev = *(lexer->current_position - 1);
	while(ft_isspace(curr))
		curr = *(++lexer->current_position);
	if (ft_is_double_quote(curr) && !(*s_quote) && prev != '\\')
		*d_quote = !(*d_quote);
	if (ft_is_single_quote(curr) && !(*d_quote) && prev != '\\')
		*s_quote = !(*s_quote);
	if (curr == '\0')
		return (0);
	if (is_operator(lexer, 0) && !(*d_quote) && !(*s_quote))
		return (0);
	return (1);
}
