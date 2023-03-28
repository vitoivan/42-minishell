/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:40:24 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/27 22:16:42 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_lkd_lst	*fill_list_of_tokens(t_ctx **ctx, t_parser_context *context)
{
	t_token		*op;
	t_lkd_lst	*lst_of_tokens;

	lst_of_tokens = lkd_lst_new_list();
	while (1)
	{
		op = get_current_token(context);
		if (!op || op->type == TOKEN_ERROR)
		{
			if (!op)
				lkd_lst_add_back(&lst_of_tokens, lkd_lst_new_node(op));
			else
			{
				lkd_lst_add_back(&lst_of_tokens, lkd_lst_new_node(op));
				lkd_lst_add_back(&lst_of_tokens, lkd_lst_new_node(NULL));
			}
			break ;
		}
		lkd_lst_add_back(&lst_of_tokens, lkd_lst_new_node(op));
		advance_to_next_token(ctx, context);
	}
	return (lst_of_tokens);
}

static t_lkd_lst	*parser_expression_linked(t_ctx **ctx,
											t_parser_context *context)
{
	t_lkd_lst	*lst_of_tokens;

	lst_of_tokens = fill_list_of_tokens(ctx, context);
	if (lst_of_tokens->size < 1)
	{
		free(lst_of_tokens);
		return (NULL);
	}
	return (lst_of_tokens);
}

t_lkd_lst	*ft_parser_linked(t_ctx **ctx, char *source)
{
	t_parser_context	context;
	t_lkd_lst			*lst;

	lexer_init(&context.lexer, source);
	parser_init(&context.parser);
	advance_to_next_token(ctx, &context);
	lst = parser_expression_linked(ctx, &context);
	if (lst)
		debug_list_of_tokens(lst);
	return (lst);
}

void	*ft_parser(t_ctx **ctx, char *source)
{
	return (ft_parser_linked(ctx, source));
}
