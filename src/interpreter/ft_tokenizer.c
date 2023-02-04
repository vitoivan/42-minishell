/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/04 18:14:17 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
	Pontos a se resolver:
		2 - precedencia do ; 
		3 - tratamento de erros de parsing
		
*/


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
	//char **variable_value;

	quote = 0;

	if ( is_command(lexer) || is_at_end(lexer) )
		return NULL;
		
	while ( !is_at_end(lexer) && !is_command(lexer)) {
	
		if (is_quote(*lexer->current_position)) {
			quote = !quote;
		}
		lexer->current_position++;

		if (ft_isspace(*(lexer->current_position))  && ft_isspace(*(lexer->current_position + 1)))
			break;
	}
	if (quote) {
		ft_printf("Parser Error, UNQUOTED STRING\n");
		exit(UNQUOTED_STRING_ERROR);
	}
	return (mk_token(lexer, TOKEN_COMMAND));
}

static Token *scan_operator(Lexer *lexer) {
	while ( !is_at_end(lexer) && is_command(lexer) ) {
		lexer->current_position++;
	}
	if (is_at_end(lexer)) {
		return NULL; // return token with error
	}
	if (ft_strncmp(lexer->start, ";", 1) == 0)
		return (mk_token(lexer, TOKEN_HIGH_OPERATOR));
	return (mk_token(lexer, TOKEN_OPERATOR));
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

