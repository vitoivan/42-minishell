/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/19 21:45:53 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*mk_token(t_ctx **ctx, t_lexer *lexer, BYTE variable, t_token_type type)
{
	t_token			*token;
	char 			**args;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	if (variable)
		token_string_builder(token, ctx, lexer);
	else
	{
		token->size = (UINT)(lexer->current_position - lexer->start);
		token->start = ft_strndup(lexer->start, token->size);
	}
	if (token->type != TOKEN_ERROR)
	{
		if (type == TOKEN_COMMAND)
		{
			args = ft_split(token->start, ' ');
			token->command = *args;
			token->args = args + 1;
		}
		else {
			token->args	= NULL;
			token->command = NULL;
		}
		token->type = type;
	}
	return (token);
}

t_token	*mk_wildcard_token(t_lexer *lexer)
{
	t_token	*token;
	char **args;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = TOKEN_COMMAND;
	token->start = ft_mk_wildcard_command(lexer);
	args = ft_split(token->start, ' ');
	token->command = *args;
	token->args = args + 1;
	token->size = ft_strlen(token->start);
	return (token);
}

t_token	*scan_command(t_ctx **ctx, t_parser_context *context)
{
	BYTE	double_quote;
	BYTE	variable;
	BYTE	single_quote;
	t_token	*token;

	double_quote = 0;
	variable = 0;
	single_quote = 0;
	if (is_operator(&context->lexer, 0) || is_at_end(&context->lexer))
		return (NULL);
	token = token_scan_command_run(&context->lexer, &variable,
			&single_quote, &double_quote);
	if (token)
		return (token);
	if (single_quote || double_quote)
		if ((single_quote && double_quote))
			return (ft_mk_generic_token(TOKEN_ERROR,
					ft_strdup("minishell: unquoted string error"), 0));
	return (mk_token(ctx, &context->lexer, variable, TOKEN_COMMAND));
}

t_token	*scan_operator(t_ctx **ctx, t_parser_context *context)
{
	t_token_type type;
	
	type = ft_get_token_type(&context->lexer);
	while (!is_at_end(&context->lexer) && is_operator(&context->lexer, 0))
		context->lexer.current_position++;
	if (is_at_end(&context->lexer) && is_operator(&context->lexer, 1))
		return (ft_mk_generic_token(TOKEN_ERROR,
				ft_strdup("minishell: Error, invalid Syntax"),
				0));
	if (!get_previus_token(context) || get_previus_token(context)->type == TOKEN_ERROR)
		return (ft_mk_generic_token(TOKEN_ERROR,
				ft_strdup("minishell: Error, invalid Syntax"),
				0));
	if (ft_strlen(context->lexer.current_position) < 1)
		return (NULL);
	
	
	return (mk_token(ctx, &context->lexer, 0, type));
}

t_token	*scan_here_document(t_lexer *lexer)
{
	char	*delimiter;
	char	*final_line;

	lexer->start = lexer->current_position;
	while (!ft_isspace(*lexer->current_position) && !is_at_end(lexer))
		lexer->current_position++;
	delimiter = ft_strndup(lexer->start,
			lexer->current_position - lexer->start);
	if (*delimiter == '\0' || is_operator(lexer, 1))
		return (ft_mk_generic_token(TOKEN_ERROR,
				ft_strdup("Error: Invalid Syntax"),
				0));
	final_line = token_here_doc_args(delimiter);
	free(delimiter);
	return (ft_mk_generic_token(TOKEN_OPERATOR_HERE_DOC_ARGS, final_line,
			ft_strlen(final_line)));
}
