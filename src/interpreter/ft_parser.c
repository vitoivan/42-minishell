/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:40:24 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/18 11:19:28 by vivan-de         ###   ########.fr       */
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

static t_ast_node	*parser_expression(t_ctx **ctx, t_parser_context *context)
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

t_ast_node	*ft_parser(t_ctx **ctx, char *source)
{
	t_parser_context	context;
	t_ast_node			*command_tree;

	lexer_init(&context.lexer, source);
	parser_init(&context.parser);
	advance_to_next_token(ctx, &context);
	command_tree = parser_expression(ctx, &context);
	return (command_tree);
}
