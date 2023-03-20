/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mk_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 22:44:00 by jv                #+#    #+#             */
/*   Updated: 2023/03/19 21:20:32 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	token_string_builder(t_token *token, t_ctx **ctx, t_lexer *lexer)
{
	t_str_builder	*sb;

	sb = string_builder(ctx, lexer->start,
			(lexer->current_position - lexer->start));
	if (sb)
	{
		token->size = sb->size;
		token->start = sb->start;
		free(sb);
	}
	else
	{
		(*ctx)->status_code = 1;
		token->type = TOKEN_ERROR;
		token->start = ft_strdup("t_lexer Error: Undefined variable\n");
	}
}

t_token	*token_scan_command_run(t_lexer *lexer,
								BYTE *var, BYTE *s_quote, BYTE *d_quote)
{	
	/* (*d_quote && *s_quote) => caso haja duas aspas definidas continue */
	while (ft_lexer_is_readable(lexer) || (*d_quote && *s_quote))
	{
		if (ft_is_double_quote(*lexer->current_position))
			*d_quote = !(*d_quote);
		if (ft_is_single_quote(*lexer->current_position))
			*s_quote = !(*s_quote);
		if (*lexer->current_position == '$'
			&& (*(lexer->current_position + 1) != '\0')
			&& !ft_isspace(*(lexer->current_position + 1)))
			*var = 1;
		if (*lexer->current_position == '*')
			return (mk_wildcard_token(lexer));
		lexer->current_position++;
	}
	return (NULL);
}

static char	*ft_mk_final_str(char *final_line, char *line, char *delimiter)
{
	char	*tmp;
	char	*curr_final_line;

	if (!final_line)
		curr_final_line = ft_strdup(line);
	else
	{
		if (!ft_strcmp(line, delimiter))
		{
			free_if_exists((void **)&line);
			return (NULL);
		}
		curr_final_line = ft_strjoin(final_line, "\n");
		free_if_exists((void **)&final_line);
		tmp = curr_final_line;
		curr_final_line = ft_strjoin(curr_final_line, line);
		free_if_exists((void **)&tmp);
	}
	return (curr_final_line);
}

char	*token_here_doc_args(char *delimiter)
{
	char	*line;
	char	*final_line;
	char	*tmp;

	tmp = NULL;
	final_line = NULL;
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			free_if_exists((void **)&line);
			break ;
		}
		tmp = ft_mk_final_str(tmp, line, delimiter);
		if (!tmp)
			break ;
		final_line = tmp;
		free_if_exists((void **)&line);
	}
	return (final_line);
}
