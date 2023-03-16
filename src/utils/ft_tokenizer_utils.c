/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:51:11 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/16 13:58:26 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*get_current_token(t_parser_context *context)
{
	return (context->parser.current_token);
}

t_token	*get_previus_token(t_parser_context *context)
{
	return (context->parser.previus_token);
}

t_token	*ft_mk_generic_token(t_token_type type, char *start, unsigned int size)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->size = size;
	token->start = start;
	return (token);
}

char	*ft_strndup(const char *str, UINT n)
{
	char	*new;

	new = NULL;
	new = ft_calloc(sizeof(char), n + 1);
	ft_strlcpy(new, str, n + 1);
	return (new);
}
