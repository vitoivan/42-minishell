/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 22:16:59 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/19 13:01:17 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ast_free_binary_exp_node(t_ast_node *node)
{
	ast_node_free(node->u_as.s_binary_expression.left);
	ast_node_free(node->u_as.s_binary_expression.right);
	ast_free_command_node(node);
}

void	ast_node_free(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
		ast_free_command_node(node);
	else
		ast_free_binary_exp_node(node);
}

void	parser_init(t_parser *parser)
{
	parser->current_token = NULL;
	parser->previus_token = NULL;
	parser->had_error = 0;
}
