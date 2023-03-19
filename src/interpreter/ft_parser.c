/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:40:24 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/19 19:09:10 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_ast_node	*mk_node_command(t_token *token)
{
	t_ast_node	*node;

	node = ft_calloc(sizeof(t_ast_node), 1);
	if (!node)
		return (NULL);
	if (!token)
		node->type = NODE_INVALID;
	else
		node->type = get_node_type(token);
	node->token = token;
	return (node);
}

static t_ast_node	*mk_node_binary_expression(t_token *token, t_ast_node *left,
		t_ast_node *right)
{
	t_ast_node	*node;

	node = ft_calloc(sizeof(t_ast_node), 1);
	if (!node)
		return (NULL);
	node->type = get_node_type(token);
	node->token = token;
	node->u_as.s_binary_expression.left = left;
	node->u_as.s_binary_expression.right = right;
	return (node);
}

static t_ast_node	*expression_builder(t_ctx **ctx, t_parser_context *context)
{
	t_ast_node	*node;
	t_ast_node	*right;
	t_token		*operator;

	node = mk_node_command(get_previus_token(context));
	operator = get_current_token(context);
	if (!operator || operator->type == TOKEN_COMMAND)
		return (node);
	while (1)
	{
		operator = get_current_token(context);
		if (!operator || operator->type == TOKEN_ERROR)
			break ;
		advance_to_next_token(ctx, context);
		right = mk_node_command(get_current_token(context));
		node = mk_node_binary_expression(operator, node, right);
		advance_to_next_token(ctx, context);
	}
	if (operator && operator->type == TOKEN_ERROR)
	{
		clean_token_with_error(operator);
		return (NULL);
	}
	return (node);
}



static t_ast_node	*parser_expression_tree(t_ctx **ctx, t_parser_context *context)
{
	advance_to_next_token(ctx, context);
	if (get_previus_token(context) == NULL)
		return (NULL);
	if (get_previus_token(context)->type == TOKEN_ERROR)
	{
		clean_token_with_error(get_previus_token(context));
		return (NULL);
	}
	if (get_current_token(context) == NULL)
		return (mk_node_command(get_previus_token(context)));
	return (expression_builder(ctx, context));
}


static t_lkd_lst *parser_expression_linked(t_ctx **ctx, t_parser_context *context)
{
	t_token *operator;
	t_lkd_lst *lst_of_tokens;


	lst_of_tokens = lkd_lst_new_list();
	while(1) {
		operator = get_current_token(context);
		if (!operator || operator->type == TOKEN_ERROR)
		{
			lkd_lst_add_back(&lst_of_tokens, lkd_lst_new_node(operator));
			break ;
		}
		lkd_lst_add_back(&lst_of_tokens, lkd_lst_new_node(operator));
		advance_to_next_token(ctx, context);
	}
	if (lst_of_tokens->size < 1) {
		free(lst_of_tokens);
		return (NULL);
	}
	return (lst_of_tokens);
}


t_ast_node	*ft_parser_tree(t_ctx **ctx, char *source)
{
	t_parser_context	context;
	t_ast_node			*command_tree;

	lexer_init(&context.lexer, source);
	parser_init(&context.parser);
	advance_to_next_token(ctx, &context);
	command_tree = parser_expression_tree(ctx, &context);
	return (command_tree);
}

t_lkd_lst *ft_parser_linked(t_ctx **ctx, char *source)
{
	t_parser_context	context;
	t_lkd_lst *lst;

	lexer_init(&context.lexer, source);
	parser_init(&context.parser);
	advance_to_next_token(ctx, &context);
	
	lst = parser_expression_linked(ctx, &context);

	if (lst)
		debug_list_of_tokens(lst);
	lkd_lst_kill_list(&lst, del_token_list);
	return (NULL);

	//return (parser_expression_linked(ctx, &context));

}

void *ft_parser(t_ctx **ctx, char *source)
{
	if (USE_LIST)
		return (ft_parser_linked(ctx, source));
	return (ft_parser_tree(ctx, source));
}
