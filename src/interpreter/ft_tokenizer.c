/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/05 14:22:28 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
	Pontos a se resolver:
		2 - precedencia do ; 
		3 - tratamento de erros de parsing
		
*/


#include "../../includes/minishell.h"

static Token *mk_token(Lexer *lexer, TokenType type, byte variable) {
	Token *token; 

	token = ft_calloc(1, sizeof(Token));

	if (!token) 
		return (NULL);
	
	token->type = type;
	if (variable) {
		StringBuilder *sb = string_builder(lexer->start, (lexer->current_position - lexer->start));
		token->size  = sb->size;
		token->start = sb->start;
		free(sb); 
	} else {
		token->size = (uint) (lexer->current_position - lexer->start);
		token->start = ft_strndup(lexer->start, token->size);
	}
	token->error_msg = NULL;
	return (token);
}

static Token *scan_command(Lexer *lexer) {
	byte quote;
	byte variable;
	
	quote    = 0;
	variable = 0;


	if ( is_command(lexer) || is_at_end(lexer) )
		return NULL;
		
	while (!is_at_end(lexer) && !is_command(lexer)) {
	
		if (ft_isquote(*lexer->current_position)) {
			quote = !quote;
		}
		
		if ( *lexer->current_position == '$' )
			variable = 1;

		lexer->current_position++;
	}
	if (quote) {
		ft_printf("Parser Error, UNQUOTED STRING\n");
		exit(UNQUOTED_STRING_ERROR);
	}
	if (!is_at_end(lexer))
		lexer->current_position--;

	return (mk_token(lexer, TOKEN_COMMAND, variable));
}

static Token *scan_operator(Lexer *lexer) {
	while ( !is_at_end(lexer) && is_command(lexer) ) {
		lexer->current_position++;
	}
	if (is_at_end(lexer)) {
		return NULL; // return token with error
	}
	if (ft_strncmp(lexer->start, ";", 1) == 0)
		return (mk_token(lexer, TOKEN_HIGH_OPERATOR, 0));
	return (mk_token(lexer, TOKEN_OPERATOR, 0));
}	

static Token *lexer_next_token(ParserContext *context) {
	Token *new_current_token;

	skip_white_spaces(&context->lexer);
	
	new_current_token = scan_command(&context->lexer);
	if (!new_current_token)
		new_current_token = scan_operator(&context->lexer);
	if (!new_current_token)
		return (NULL);
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
}

