/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:21:11 by victor            #+#    #+#             */
/*   Updated: 2023/01/10 18:55:27 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define BOOL int
# define SINGLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define BUFFER_SIZE 4096
# define uint unsigned int
# define byte unsigned char

enum	e_bool
{
	False = 0,
	True = 1
};

enum	e_erros
{
	UNQUOTED_STRING_ERROR,
	MEMORY_ALLOC_ERROR
};

typedef enum  {
  NODE_INVALID,
  NODE_COMMAND,
  NODE_AND,
  NODE_OR,
  NODE_PIPE,
  NODE_REDIRECT, 
  NODE_REDIRECT_APPEND,
  NODE_SEMICOLON
} AstNodeType;

typedef enum  {
  TOKEN_ERROR,
  TOKEN_COMMAND,
  TOKEN_OPERATOR
} TokenType;

typedef struct {
  const char *start;
  const char *current_position;
} Lexer;

typedef struct {
  char *start;
  char *error_msg;
  TokenType type;
  uint size;
} Token;

typedef struct parser_t {
  Token *previus_token;
  Token *current_token;
  byte had_error;
} Parser;

typedef struct {
  Lexer lexer;
  Parser parser;
} ParserContext;

typedef struct ast_node_t {
  AstNodeType type;
  Token *token;
  byte had_error;
  union {
    struct {
      struct ast_node_t *left;
      struct ast_node_t *right;
    } binaryExpression;
  } as;
} AstNode;


#endif
