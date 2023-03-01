/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:21:11 by victor            #+#    #+#             */
/*   Updated: 2023/02/28 22:23:52 by jv               ###   ########.fr       */
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
	NODE_REDIRECT_INPUT,
	NODE_HERE_DOCUMENT,
	NODE_REDIRECT,
	NODE_REDIRECT_APPEND,
	NODE_SEMICOLON
}								e_ast_node_type;

typedef enum
{
	PREC_NONE,
	PREC_HIGH
}								e_precedence;

typedef enum
{
	TOKEN_ERROR,
	TOKEN_COMMAND,
	TOKEN_OPERATOR,
	TOKEN_HIGH_OPERATOR
}								t_token_type;

typedef struct s_lexer
{
	char						*start;
	char						*current_position;
}								t_lexer;

typedef struct
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
	e_ast_node_type				type;
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
