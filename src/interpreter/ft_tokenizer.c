/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/11 19:12:29 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Pontos a se resolver:
		2 - precedencia do ; 
		3 - tratamento de erros de parsing
		
*/

#include "../../includes/minishell.h"

static t_token	*lexer_next_token(t_ctx **ctx, t_lexer *lexer);
static t_token	*scan_command(t_ctx **ctx, t_lexer *lexer);
static t_token	*scan_operator(t_ctx **ctx, t_lexer *lexer);

static t_token	*mk_token(t_ctx **ctx, t_lexer *lexer, BYTE variable)
{
	t_token			*token;
	t_str_builder	*sb;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	if (variable)
	{
		sb = string_builder(ctx, lexer->start, (lexer->current_position
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
			errno = 1;
			(*ctx)->status_code = 1;
			token->type = TOKEN_ERROR;
			token->error_msg = "t_lexer Error: Undefined variable\n";
		}
	}
	else
	{
		token->size = (UINT)(lexer->current_position - lexer->start);
		token->start = ft_strndup(lexer->start, token->size);
	}
	token->type = ft_get_token_type(token);
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

t_token	*ft_tmp_next_token(t_lexer *lexer)
{
	char	*curr;
	t_token	*tmp_token;

	curr = lexer->current_position;
	tmp_token = ft_calloc(1, sizeof(t_token));
	while (!ft_isspace(*lexer->current_position) && !is_at_end(lexer))
		lexer->current_position++;
	tmp_token->start = ft_strndup(curr + 1, lexer->current_position - curr);
	tmp_token->size = (UINT)(lexer->current_position - curr);
	tmp_token->type = ft_get_token_type(tmp_token);
	lexer->current_position = curr;
	return (tmp_token);
}

static t_token	*scan_command(t_ctx **ctx, t_lexer *lexer)
{
	BYTE	quote;
	BYTE	variable;
	BYTE	single_quote;

	//t_token *next;
	quote = 0;
	variable = 0;
	single_quote = 0;
	if (is_operator(lexer) || is_at_end(lexer))
		return (NULL);
	/*if ((next = ft_tmp_next_token(lexer)) != NULL)
	{
		if (next->type)
	}*/
	while (!is_at_end(lexer) && (!is_operator(lexer) || quote || single_quote))
	{
		if (ft_is_double_quote(*lexer->current_position))
			quote = !quote;
		if (ft_is_single_quote(*lexer->current_position))
			single_quote = !single_quote;
		if (*lexer->current_position == '$')
			variable = 1;
		if (*lexer->current_position == '*')
			return (mk_wildcard_token(lexer));
		lexer->current_position++;
	}
	if (quote || single_quote)
	{
		ft_printf("t_parser Error, UNQUOTED STRING\n");
		exit(UNQUOTED_STRING_ERROR);
	}
	if (!is_at_end(lexer))
		lexer->current_position--;
	return (mk_token(ctx, lexer, variable));
}

static t_token	*scan_operator(t_ctx **ctx, t_lexer *lexer)
{
	while (!is_at_end(lexer) && is_operator(lexer))
		lexer->current_position++;
	if (is_at_end(lexer))
		return (NULL); // return token with error
	return (mk_token(ctx, lexer, 0));
}

static t_token	*lexer_next_token(t_ctx **ctx, t_lexer *lexer)
{
	t_token	*new_current_token;

	skip_white_spaces(lexer);
	new_current_token = scan_command(ctx, lexer);
	if (!new_current_token)
		new_current_token = scan_operator(ctx, lexer);
	if (!new_current_token)
		return (NULL);
	lexer->start = lexer->current_position;
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
	context->parser.current_token = lexer_next_token(ctx, &context->lexer);
}
