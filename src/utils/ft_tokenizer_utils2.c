/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:51:11 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/30 08:15:06 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

BYTE	is_at_end(t_lexer *lexer)
{
	return (*lexer->current_position == '\0'
		|| *lexer->current_position == '\n');
}

BYTE	is_operator(t_lexer *lexer, UINT offset)
{
	char	*c;

	c = (lexer->current_position - offset);
	if (ft_strncmp(c, "&&", 2) == 0)
		return (2);
	if (ft_strncmp(c, "||", 2) == 0)
		return (2);
	if (ft_strncmp(c, ">>", 2) == 0)
		return (2);
	if (ft_strncmp(c, "<<", 2) == 0)
		return (2);
	if (ft_strncmp(c, "|", 1) == 0)
		return (1);
	if (ft_strncmp(c, ">", 1) == 0)
		return (1);
	if (ft_strncmp(c, "<", 1) == 0)
		return (1);
	return (0);
}

t_token_type	ft_get_token_type(t_lexer *lexer)
{
	char	*curr;

	curr = lexer->current_position;
	if (ft_strncmp(curr, "&&", 2) == 0)
		return (TOKEN_OPERATOR_AND);
	if (ft_strncmp(curr, "||", 2) == 0)
		return (TOKEN_OPERATOR_OR);
	if (ft_strncmp(curr, "|", 1) == 0)
		return (TOKEN_OPERATOR_PIPE);
	if (ft_strncmp(curr, "<<", 2) == 0)
		return (TOKEN_OPERATOR_HERE_DOC);
	if (ft_strncmp(curr, "<", 1) == 0)
		return (TOKEN_OPERATOR_REDIRECT_INPUT);
	if (ft_strncmp(curr, ">>", 2) == 0)
		return (TOKEN_OPERATOR_REDIRECT_APPEND);
	if (ft_strncmp(curr, ">", 1) == 0)
		return (TOKEN_OPERATOR_REDIRECT);
	if (ft_strncmp(curr, ";", 1) == 0)
		return (TOKEN_OPERATOR_SEMICOLON);
	return (TOKEN_ERROR);
}

void	skip_white_spaces(t_lexer *lexer)
{
	while (ft_isspace(*lexer->current_position) && !is_at_end(lexer))
		lexer->current_position++;
	lexer->start = lexer->current_position;
}

void	lexer_init(t_lexer *lexer, char *source)
{
	lexer->start = source;
	lexer->current_position = source;
}
