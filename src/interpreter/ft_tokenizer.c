/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/04 14:28:14 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Pontos a se resolver:
		2 - precedencia do ; 
		3 - tratamento de erros de parsing
		
*/

#include "../../includes/minishell.h"

static t_token	*mk_token(t_lexer *lexer, t_token_type type, BYTE variable)
{
	t_token			*token;
	t_str_builder	*sb;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (variable)
	{
		sb = string_builder(lexer->start, (lexer->current_position
					- lexer->start));
		if (sb)
		{
			token->size = sb->size;
			token->start = sb->start;
			free(sb);
		}
		else
		{
			ft_printf("LexerError: Undefined variable\n");
			token->type = TOKEN_ERROR;
			token->error_msg = "t_lexer Error: Undefined variable\n";
		}
	}
	else
	{
		token->size = (UINT)(lexer->current_position - lexer->start);
		token->start = ft_strndup(lexer->start, token->size);
	}
	return (token);
}

static t_token	*mk_wildcard_token(t_lexer *lexer)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = TOKEN_COMMAND;
	token->start = ft_mk_wildcard_command(lexer);
	token->size = ft_strlen(token->start);
	return (token);
}

static t_token	*scan_command(t_lexer *lexer)
{
	BYTE	quote;
	BYTE	variable;

	quote = 0;
	variable = 0;
	if (is_operator(lexer) || is_at_end(lexer))
		return (NULL);
	while (!is_at_end(lexer) && (!is_operator(lexer) || quote))
	{
		if (ft_is_double_quote(*lexer->current_position))
			quote = !quote;
		if (*lexer->current_position == '$')
			variable = 1;
		if (*lexer->current_position == '*')
			return (mk_wildcard_token(lexer));
		lexer->current_position++;
	}
	if (quote)
	{
		ft_printf("t_parser Error, UNQUOTED STRING\n");
		exit(UNQUOTED_STRING_ERROR);
	}
	if (!is_at_end(lexer))
		lexer->current_position--;
	return (mk_token(lexer, TOKEN_COMMAND, variable));
}

static t_token	*scan_operator(t_lexer *lexer)
{
	while (!is_at_end(lexer) && is_operator(lexer))
		lexer->current_position++;
	// if (!strncmp(lexer->current_position - 1, "||", 2))
	// 	lexer->current_position++;
	if (is_at_end(lexer))
	{
		return (NULL); // return token with error
	}
	if (ft_strncmp(lexer->start, ";", 1) == 0)
		return (mk_token(lexer, TOKEN_HIGH_OPERATOR, 0));
	return (mk_token(lexer, TOKEN_OPERATOR, 0));
}

static t_token	*lexer_next_token(t_parser_context *context)
{
	t_token	*new_current_token;

	skip_white_spaces(&context->lexer);
	new_current_token = scan_command(&context->lexer);
	if (!new_current_token)
		new_current_token = scan_operator(&context->lexer);
	if (!new_current_token)
		return (NULL);
	context->lexer.start = context->lexer.current_position;
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

void	advance_to_next_token(t_parser_context *context)
{
	context->parser.previus_token = context->parser.current_token;
	context->parser.current_token = lexer_next_token(context);
}
