/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:21:11 by victor            #+#    #+#             */
/*   Updated: 2023/02/05 14:52:39 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../libs/libft/includes/libft.h"
# include "ctx.h"
# include "define.h"

BOOL		get_line_from_terminal(char **line, t_ctx *);
void		free_if_exists(void **data);
void		free_token(void *data);
void		skip_whitespace(char **line, int always_skip_one);
void		print_terminal(t_ctx *ctx);
char		*get_hostname(char **envp);
void		print_lkd_list(t_lkd_lst **list);

/*	parser functions	*/
AstNode		*ft_parser(char *source);
AstNodeType	get_node_type(Token *token);
void		ast_node_free(AstNode *node);
void		parser_init(Parser *parser);
t_lkd_lst	*get_head_node(AstNode *node);

/*  tokenizer functions */
void		del_token(Token *token);
void		advance_to_next_token(ParserContext *context);
void		lexer_init(Lexer *lexer, char *source);
void		skip_white_spaces(Lexer *lexer);
byte		is_at_end(Lexer *lexer);
byte		is_command(Lexer *lexer);
Token		*get_current_token(ParserContext *context);
Token		*get_previus_token(ParserContext *context);
char		*ft_strndup(const char *str, uint n);
Precedence	get_precedence(Token *token);
int			ft_isspace(int c);
BOOL		ft_isquote(char c);
void		skip_quotes(char **line);

/* debug functions */
void		debug_command_tree(AstNode *root);
void		debug_token(Token *token);

/*   string builder       */
StringBuilder   *string_builder(const char *s, int t_size);
#endif
