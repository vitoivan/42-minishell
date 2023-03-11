/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:21:11 by victor            #+#    #+#             */
/*   Updated: 2023/03/10 22:37:31 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# include "../libs/libft/includes/libft.h"

# define BOOL int
# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define BUFFER_SIZE 4096
# define DEBUG 1
# define UINT unsigned int
# define BYTE unsigned char
# define HERE_DOC "EOF"
# define HERE_DOC_2 "_"

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

typedef enum e_ast_node_type
{
	NODE_INVALID,
	NODE_COMMAND,
	NODE_AND,
	NODE_OR,
	NODE_PIPE,
	NODE_REDIRECT_INPUT,
	NODE_HERE_DOCUMENT,
	NODE_REDIRECT,
	NODE_REDIRECT_APPEND,
	NODE_SEMICOLON
}								t_ast_node_type;

typedef enum e_precedence
{
	PREC_NONE,
	PREC_HIGH
}								t_precedence;

typedef enum e_token_type
{
	TOKEN_ERROR,
	TOKEN_COMMAND,
	TOKEN_OPERATOR,
	TOKEN_OPERATOR_HERE_DOC,
	TOKEN_OPERATOR_REDIRECT_INPUT,
	TOKEN_OPERATOR_AND,
	TOKEN_OPERATOR_OR,
	TOKEN_OPERATOR_PIPE,
	TOKEN_OPERATOR_REDIRECT,
	TOKEN_OPERATOR_REDIRECT_APPEND,
	TOKEN_OPERATOR_SEMICOLON,
	TOKEN_HIGH_OPERATOR
}								t_token_type;

typedef struct s_lexer
{
	char						*start;
	char						*current_position;
}								t_lexer;

typedef struct s_token
{
	char						*start;
	char						*error_msg;
	t_token_type				type;
	UINT						size;
}								t_token;

typedef struct s_parser
{
	t_token						*previus_token;
	t_token						*current_token;
	BYTE						had_error;
}								t_parser;

typedef struct s_parser_context
{
	t_lexer						lexer;
	t_parser					parser;
}								t_parser_context;

typedef struct s_ast_node
{
	t_ast_node_type				type;
	t_token						*token;
	BYTE						had_error;
	union
	{
		struct
		{
			struct s_ast_node	*left;
			struct s_ast_node	*right;
		} binaryExpression;
		struct
		{
			t_lkd_lst			*nodes;
		} expressions;
	} as;
}								t_ast_node;

typedef struct s_string_builder
{
	UINT						size;
	char						*start;
}								t_str_builder;

#endif
