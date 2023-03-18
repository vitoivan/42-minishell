/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 15:21:11 by victor            #+#    #+#             */
/*   Updated: 2023/03/18 09:53:35 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../libs/libft/includes/libft.h"
# include "ctx.h"
# include "define.h"

typedef struct s_str_builder_internal
{
	char		*new_str;
	char		*env_name;
	char		*env_value;
	int			ini_pos;
	int			i;
	int			j;
	int			real_size;
	int			single_quote;
	int			env_len;
}				t_str_builder_internal;

typedef struct s_str_builder_real_size
{
	int			value_size;
	int			i;
	char		*env_value;
	char		*env_name;
	int			ini_pos;
	int			env_name_len;
	int			env_value_len;
	int			aux;
}				t_str_builder_real_size_internal;

BOOL			get_line_from_terminal(char **line, t_ctx *ctx);
void			free_if_exists(void **data);
void			free_token(void *data);
int				skip_whitespace(char **line, int always_skip_one);
char			*get_prompt(t_ctx *ctx);
char			*get_hostname(char **envp);
void			print_lkd_list(t_lkd_lst **list);

/*	parser functions	*/
t_ast_node		*ft_parser(t_ctx **ctx, char *source);
t_ast_node_type	get_node_type(t_token *token);
void			ast_node_free(t_ast_node *node);
void			parser_init(t_parser *parser);
t_lkd_lst		*get_head_node(t_ast_node *node);
void 			clean_token_with_error(t_token *token);

/*  tokenizer functions */
void			exec_tree(t_ast_node *node, t_ctx **ctx);
void			del_token(t_token *token);
void			advance_to_next_token(t_ctx **ctx, t_parser_context *context);
void			lexer_init(t_lexer *lexer, char *source);
void			skip_white_spaces(t_lexer *lexer);
void			skip_quotes(char **line);
void			clear_splitted(char ***splitted);
void			ast_free_command_node(t_ast_node *node);
void 			token_string_builder(t_token *token, t_ctx **ctx, t_lexer *lexer);
BYTE			is_at_end(t_lexer *lexer);
BYTE			is_operator(t_lexer *lexer, UINT offset);
BYTE			ft_strmatch(char *entry, char *pattern);
char			*ft_strndup(const char *str, UINT n);
char			*token_here_doc_args(char *delimiter);
t_precedence	get_precedence(t_token *token);
int				ft_isspace(int c);
int				real_string_size(t_ctx **ctx, char *s, int size);
BOOL			ft_is_double_quote(char c);
BOOL			ft_is_single_quote(char c);
BOOL			ft_isquote(char c);
t_token_type	ft_get_token_type(t_token *token);
t_token			*token_scan_command_run(t_lexer *lexer, BYTE *var, BYTE *s_quote, BYTE *d_quote);
t_token			*get_current_token(t_parser_context *context);
t_token			*get_previus_token(t_parser_context *context);
t_token			*ft_mk_generic_token(t_token_type type, char *start, UINT size	);
t_token			*lexer_next_token(t_ctx **ctx, t_lexer *lexer, BYTE is_here_doc);
t_token			*scan_here_document(t_lexer *lexer);
t_token			*scan_operator(t_ctx **ctx, t_lexer *lexer);
t_token			*scan_command(t_ctx **ctx, t_lexer *lexer);
t_token			*mk_wildcard_token(t_lexer *lexer);
t_token			*mk_token(t_ctx **ctx, t_lexer *lexer, BYTE variable);



/* Error handle utils */
void			print_errno(t_ctx **ctx, char *line);

/* debug functions */
void			debug_command_tree(t_ast_node *root);
void			debug_token(t_token *token);

/*   string builder       */
t_str_builder	*string_builder(t_ctx **ctx, const char *s, int t_size);

/*   wildcard             */
char			*ft_mk_wildcard_command(t_lexer *lexer);

char			*ctx_get_env(t_ctx **ctx, char *env_name);
void			handle_signals(void);
int				string_builder_free_everything(void *rs, void *sb,
					const char *want_free);
#endif
