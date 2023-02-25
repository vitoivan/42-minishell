/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:21:11 by victor            #+#    #+#             */
/*   Updated: 2023/02/25 15:21:04 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# include "../libs/libft/includes/libft.h"

# define BOOL int
# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define BUFFER_SIZE 4096
# define DEBUG 0
# define uint unsigned int
# define byte unsigned char

enum							e_bool
{
	False = 0,
	True = 1
};

enum							e_erros
{
	UNQUOTED_STRING_ERROR,
	MEMORY_ALLOC_ERROR,
	PARSER_ERROR
};

typedef enum
{
	NODE_INVALID,
	NODE_COMMAND,
	NODE_AND,
	NODE_OR,
	NODE_PIPE,
	NODE_REDIRECT,
	NODE_REDIRECT_APPEND,
	NODE_SEMICOLON
}								AstNodeType;

typedef enum
{
	PREC_NONE,
	PREC_HIGH
}								Precedence;

typedef enum
{
	TOKEN_ERROR,
	TOKEN_COMMAND,
	TOKEN_OPERATOR,
	TOKEN_HIGH_OPERATOR
}								TokenType;

typedef struct
{
	char					*start;
	char					*current_position;
}								Lexer;

typedef struct
{
	char						*start;
	char						*error_msg;
	TokenType					type;
	uint						size;
}								Token;

typedef struct parser_t
{
	Token						*previus_token;
	Token						*current_token;
	byte						had_error;
}								Parser;

typedef struct
{
	Lexer						lexer;
	Parser						parser;
}								ParserContext;

typedef struct ast_node_t
{
	AstNodeType					type;
	Token						*token;
	byte						had_error;
	union
	{
		struct
		{
			struct ast_node_t	*left;
			struct ast_node_t	*right;
		} binaryExpression;
		struct
		{
			t_lkd_lst			*nodes;
		} expressions;
	} as;
}								AstNode;

typedef struct
{
	uint						size;
	char						*start;
}								StringBuilder;

#endif
