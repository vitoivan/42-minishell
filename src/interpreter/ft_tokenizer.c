/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/12 19:38:00 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Pontos a se resolver:
		2 - precedencia do ; 
		3 - tratamento de erros de parsing
		
*/

#include "../../includes/minishell.h"


static t_token	*mk_token(t_ctx **ctx, t_lexer *lexer, BYTE variable)
{
	t_token			*token;
	t_str_builder	*sb;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	if (variable)
	{
		sb = string_builder(ctx, lexer->start, (lexer->current_position
					- lexer->start));
		if (sb)
		{
			token->size = sb->size;
			token->start = sb->start;
			free(sb);
		}
		else
		{
			ft_putstr_fd("LexerError: Undefined variable\n", STDERR_FILENO);
			errno = 1;
			(*ctx)->status_code = 1;
			token->type = TOKEN_ERROR;
			token->error_msg = "t_lexer Error: Undefined variable\n";
		}
	}
	else
	{
		token->size = (UINT)(lexer->current_position - lexer->start);
		token->start = ft_strndup(lexer->start, token->size);
	}
	token->type = ft_get_token_type(token);
	return (token);
}

static t_token	*mk_wildcard_token(t_lexer *lexer)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = TOKEN_COMMAND;
	token->start = ft_mk_wildcard_command(lexer);
	token->size = ft_strlen(token->start);
	return (token);
}

t_token	*ft_tmp_next_token(t_lexer *lexer)
{
	char	*curr;
	t_token	*tmp_token;

	curr = lexer->current_position;
	tmp_token = ft_calloc(1, sizeof(t_token));
	while (!ft_isspace(*lexer->current_position) && !is_at_end(lexer))
		lexer->current_position++;
	tmp_token->start = ft_strndup(curr + 1, lexer->current_position - curr);
	tmp_token->size = (UINT)(lexer->current_position - curr);
	tmp_token->type = ft_get_token_type(tmp_token);
	lexer->current_position = curr;
	return (tmp_token);
}

static t_token	*scan_command(t_ctx **ctx, t_lexer *lexer)
{
	BYTE	quote;
	BYTE	variable;
	BYTE 	single_quote;

	//t_token *next;
	quote = 0;
	variable = 0;
	single_quote = 0;
	if (is_operator(lexer) || is_at_end(lexer))
		return (NULL);
	while (!is_at_end(lexer) && (!is_operator(lexer) || quote || single_quote))
	{
		if (ft_is_double_quote(*lexer->current_position))
			quote = !quote;
		if (ft_is_single_quote(*lexer->current_position))
			single_quote = !single_quote;
		if (*lexer->current_position == '$')
			variable = 1;
		if (*lexer->current_position == '*')
			return (mk_wildcard_token(lexer));
		lexer->current_position++;
	}
	if (quote || single_quote)
	{
		ft_putstr_fd("t_parser Error, UNQUOTED STRING\n", STDERR_FILENO);
		exit(UNQUOTED_STRING_ERROR);
	}
	if (!is_at_end(lexer))
		lexer->current_position--;
	return (mk_token(ctx, lexer, variable));
}

static t_token	*scan_operator(t_ctx **ctx, t_lexer *lexer)
{
	while (!is_at_end(lexer) && is_operator(lexer))
		lexer->current_position++;
	if (is_at_end(lexer))
		return (NULL); // return token with error
	
	return mk_token(ctx, lexer, 0);
}

static t_token *scan_here_document(t_lexer *lexer)
{
	char *line;
	char *final_line;
	t_token *token;

	line 	   = NULL;
	final_line = NULL;


	if ((token = ft_calloc(1, sizeof(t_token))) == NULL)
		return (NULL);

	if (!(*lexer->current_position == '_' ) || !ft_strcmp(lexer->current_position, "EOF"))
	{
			token->start = ft_strdup("minishell: erro de sintaxe próximo ao token inesperado `newline'");
			token->size  = ft_strlen(token->start);
			token->type  = TOKEN_ERROR;
			return (token);
	}
	while (1)
	{
		line = readline("heredoc> ");
		if (!line) {
			free_if_exists((void **)&line);
			break;
		}
		if (!final_line)
			final_line = ft_strdup(line);
		else
		{
			if (!ft_strcmp(line, "_") || !ft_strcmp(line, "EOF"))
			{
				free_if_exists((void **)&line);
				break;
			}
			char *tmp = final_line;
			final_line = ft_strjoin(final_line, line);
			free_if_exists((void **)&tmp);
		}
		
		free_if_exists((void **)&line);
	}
	token->type  = TOKEN_OPERATOR_HERE_DOC_ARGS;
	token->start = final_line;
	token->size = ft_strlen(final_line);

	lexer->current_position++;
		
	return (token);
}

static t_token	*lexer_next_token(t_ctx **ctx, t_lexer *lexer, BYTE is_here_doc)
{
	t_token	*new_current_token;

	skip_white_spaces(lexer);
	if (is_here_doc)
		new_current_token = scan_here_document(lexer);
	else
	{
		new_current_token = scan_command(ctx, lexer);
		if (!new_current_token)
			new_current_token = scan_operator(ctx, lexer);
		if (!new_current_token)
			return (NULL);
	}
	return (new_current_token);
}

void	del_token(t_token *token)
{
	if (token != NULL)
	{
		free(token->start);
		free(token);
	}
}

void	advance_to_next_token(t_ctx **ctx, t_parser_context *context)
{
	context->parser.previus_token = context->parser.current_token;
	if (get_previus_token(context) && get_previus_token(context)->type == TOKEN_OPERATOR_HERE_DOC)
		context->parser.current_token = lexer_next_token(ctx, &context->lexer, 1);
	else 
		context->parser.current_token = lexer_next_token(ctx, &context->lexer, 0);
	context->lexer.start = context->lexer.current_position;
}
