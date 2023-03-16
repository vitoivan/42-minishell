/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/16 15:39:42 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static t_token	*scan_command(t_ctx **ctx, t_lexer *lexer)
{
	BYTE	quote;
	BYTE	variable;
	BYTE	single_quote;

	quote = 0;
	variable = 0;
	single_quote = 0;
	if (is_operator(lexer, 0) || is_at_end(lexer))
		return (NULL);
	while (!is_at_end(lexer) && (!is_operator(lexer, 0) || quote
			|| single_quote))
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
		if (!(quote && single_quote))
			return (ft_mk_generic_token(TOKEN_ERROR,
										ft_strdup("minishell: unquoted string error"),
										0));
	if (!is_at_end(lexer))
		lexer->current_position--;
	return (mk_token(ctx, lexer, variable));
}

static t_token	*scan_operator(t_ctx **ctx, t_lexer *lexer)
{
	while (!is_at_end(lexer) && is_operator(lexer, 0))
		lexer->current_position++;
	if (is_at_end(lexer) && is_operator(lexer, 1))
		return (ft_mk_generic_token(TOKEN_ERROR,
									ft_strdup("minishell: invalid here document operator"),
									0));
	if (ft_strlen(lexer->current_position) < 1)
		return (NULL);
	return (mk_token(ctx, lexer, 0));
}

static t_token	*scan_here_document(t_lexer *lexer)
{
	char	*line;
	char	*final_line;
	char	*tmp;
	t_token	*token;
	char	*delimiter;
	char	*tmp;

	line = NULL;
	final_line = NULL;
	tmp = NULL;
	if ((token = ft_calloc(1, sizeof(t_token))) == NULL)
		return (NULL);
	skip_white_spaces(lexer);
	tmp = lexer->current_position;
	while (!ft_isspace(*lexer->current_position) && !is_at_end(lexer))
		lexer->current_position++;
	delimiter = ft_strndup(tmp, lexer->current_position - tmp);
	if (*delimiter == '\0' || is_operator(lexer, 1))
		return (ft_mk_generic_token(TOKEN_ERROR,
									ft_strdup("Error: Here Document Syntax Error"),
									0));
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			free_if_exists((void **)&line);
			break ;
		}
		if (!final_line)
			final_line = ft_strdup(line);
		else
		{
			if (!ft_strcmp(line, delimiter))
			{
				free_if_exists((void **)&line);
				break ;
			}
			tmp = final_line;
			final_line = ft_strjoin(final_line, "\n");
			free_if_exists((void **)&tmp);
			tmp = final_line;
			final_line = ft_strjoin(final_line, line);
			free_if_exists((void **)&tmp);
		}
		free_if_exists((void **)&line);
	}
	free(delimiter);
	return (ft_mk_generic_token(TOKEN_OPERATOR_HERE_DOC_ARGS, final_line,
			ft_strlen(final_line)));
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
	if (get_previus_token(context)
		&& get_previus_token(context)->type == TOKEN_OPERATOR_HERE_DOC)
		context->parser.current_token = lexer_next_token(ctx, &context->lexer,
				1);
	else
		context->parser.current_token = lexer_next_token(ctx, &context->lexer,
				0);
	context->lexer.start = context->lexer.current_position;
}
