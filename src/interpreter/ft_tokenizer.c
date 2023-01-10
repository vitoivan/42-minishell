/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/01/10 19:09:02 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static Token *mk_token(Lexer *lexer, TokenType type) {
	Token *token; 

	token = ft_calloc(1, sizeof(Token));

	if (!token) 
		return (NULL);
	
	token->type = type;
	token->size = (uint) (lexer->current_position - lexer->start);
	token->start = ft_strndup(lexer->start, token->size);
	token->error_msg = NULL;
	return (token);
}

static Token *scan_command(Lexer *lexer) {
	uint quote;

	quote = 0;

	if ( is_command(lexer) || is_at_end(lexer) )
		return NULL;
		
	while ( !is_at_end(lexer) && !is_command(lexer)) {
		if (is_quote(*lexer->current_position)) {
			if (quote) 
			{
				lexer->current_position++;
				return (mk_token(lexer, TOKEN_COMMAND));
			}
			quote = 1;
		}
		lexer->current_position++;
	}
	if (quote) {
		// return token with error 
	}
	if ( is_command(lexer))
		lexer->current_position--;
	return (mk_token(lexer, TOKEN_COMMAND));
}

static Token *scan_operator(Lexer *lexer) {
	while ( !is_at_end(lexer) && is_command(lexer) ) {
		lexer->current_position++;
	}
	if (is_at_end(lexer)) {
		return NULL; // return token with error
	}
	return (mk_token(lexer, TOKEN_OPERATOR));
}

static Token *lexer_next_token(ParserContext *context) {
	Token *new_current_token;

	new_current_token = scan_command(&context->lexer);
	if (!new_current_token)
		new_current_token = scan_operator(&context->lexer);
	if (!new_current_token)
		return (NULL);
	skip_white_spaces(&context->lexer);
	context->lexer.start = context->lexer.current_position;
	return (new_current_token);
}

void del_token(Token *token) {
	if (token != NULL) {
		free(token->start);
		free(token);
	}
}


void advance_to_next_token(ParserContext *context) {
	context->parser.previus_token = context->parser.current_token;

	context->parser.current_token = lexer_next_token(context);
/*
	if (get_current_token(context)->type != TOKEN_ERROR)
		return ;
	exit(1); // error in current token, adjusting msg after
*/
}

