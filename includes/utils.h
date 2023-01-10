/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:21:11 by victor            #+#    #+#             */
/*   Updated: 2023/01/10 19:08:40 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

BOOL	get_line_from_terminal(char **line);
void	free_if_exists(void **data);
void	free_token(void *data);

/*	parser functions	*/
AstNode *ft_parser(char *source);
AstNodeType	get_node_type(Token *token);
void	ast_node_free(AstNode *node);
void	parser_init(Parser *parser);

/*  tokenizer functions */
void	del_token(Token *token);
void	advance_to_next_token(ParserContext *context);
void 	lexer_init(Lexer *lexer, char *source);
void	skip_white_spaces(Lexer *lexer);
byte	is_at_end(Lexer *lexer);
byte	is_quote(char ch);
byte	is_command(Lexer *lexer);
Token	*get_current_token(ParserContext *context);
Token	*get_previus_token(ParserContext *context);
char	*ft_strndup(const char *str, uint n);

/* debug functions */
void	debug_command_tree(AstNode *root);
void	debug_token(Token *token);
#endif
