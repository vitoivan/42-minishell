/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:16:59 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/16 13:51:02 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (node->type == NODE_COMMAND)
		ast_free_command_node(node);
	else if (node->type == NODE_SEMICOLON)
		ast_free_semicolon_exp_node(node);
	else
		ast_free_binary_exp_node(node);
}

void	parser_init(t_parser *parser)
{
	parser->current_token = NULL;
	parser->previus_token = NULL;
	parser->had_error = 0;
}
