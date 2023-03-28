/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:51:11 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/27 22:14:11 by jv               ###   ########.fr       */
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

t_token	*ft_mk_generic_token(t_token_type type, char *start, UINT size)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->size = size;
	token->start = start;
	token->filein = 0;
	token->fileout = 1;
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

void	ft_fill_token(t_token *token, t_token_type type)
{
	char	**args;

	if (token->type != TOKEN_ERROR)
	{
		if (type == TOKEN_COMMAND)
		{
			args = ft_split(token->start, ' ');
			token->command = *args;
			token->args = args + 1;
		}
		else
		{
			token->args = NULL;
			token->command = NULL;
		}
		token->type = type;
	}
	else
	{
		token->args = NULL;
		token->command = NULL;
	}
}
