/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:16:59 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/12 19:46:54 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast_node_type	get_node_type(t_token *token)
{
	if (token->type == TOKEN_OPERATOR_AND)
		return (NODE_AND);
	if (token->type == TOKEN_OPERATOR_OR)
		return (NODE_OR);
	if (token->type == TOKEN_OPERATOR_PIPE)
		return (NODE_PIPE);
	if (token->type == TOKEN_OPERATOR_REDIRECT_INPUT)
		return (NODE_REDIRECT_INPUT);
	if (token->type == TOKEN_OPERATOR_HERE_DOC)
		return (NODE_HERE_DOCUMENT);
	if (token->type == TOKEN_OPERATOR_HERE_DOC_ARGS)
		return (NODE_HERE_ARGS);
	if (token->type == TOKEN_OPERATOR_REDIRECT)
		return (NODE_REDIRECT);
	if (token->type == TOKEN_OPERATOR_REDIRECT_APPEND)
		return (NODE_REDIRECT_APPEND);
	if (token->type == TOKEN_OPERATOR_SEMICOLON)
		return (NODE_SEMICOLON);
	if (token->type == TOKEN_ERROR)
		return (NODE_INVALID);

	return (NODE_COMMAND);
}

static void	ast_free_command_node(t_ast_node *node)
{
	del_token(node->token);
	free(node);
}

static void	ast_free_binary_exp_node(t_ast_node *node)
{
	ast_node_free(node->as.binaryExpression.left);
	ast_node_free(node->as.binaryExpression.right);
	ast_free_command_node(node);
}

static void	ast_free_semicolon_exp_node(t_ast_node *node)
{
	t_lkd_lst	*list;
	t_lkd_node	*head;
	UINT		i;

	list = get_head_node(node);
	head = list->head;
	i = 0;
	while (i < list->size)
	{
		ast_node_free(head->content);
		head = head->next;
		i++;
	}
	free(node->as.expressions.nodes);
}

t_lkd_lst	*get_head_node(t_ast_node *node)
{
	return (node->as.expressions.nodes);
}

void	ast_node_free(t_ast_node *node)
{
	if (!node)
		return ;
	switch (node->type)
	{
	case NODE_COMMAND:
		ast_free_command_node(node);
		break ;
	case NODE_SEMICOLON:
		ast_free_semicolon_exp_node(node);
		break ;
	default:
		ast_free_binary_exp_node(node);
		break ;
	}
}

void	parser_init(t_parser *parser)
{
	parser->current_token = NULL;
	parser->previus_token = NULL;
	parser->had_error = 0;
}