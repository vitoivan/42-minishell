/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:38:20 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/11 19:17:51 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_pipe(t_ast_node *node, t_ctx **ctx)
{
	if (node->as.binaryExpression.left)
		exec_tree(node->as.binaryExpression.left, ctx);
	if (node->as.binaryExpression.right)
		exec_tree(node->as.binaryExpression.right, ctx);
}

static void	exec_and_or(t_ast_node *node, t_ctx **ctx)
{
	if (node->as.binaryExpression.left)
		exec_tree(node->as.binaryExpression.left, ctx);
	if ((node->type == NODE_AND && errno == EXIT_SUCCESS)
		|| (node->type == NODE_OR && errno != EXIT_SUCCESS))
	{
		if ((*ctx)->buffer[0])
		{
			ft_putstr_fd((*ctx)->buffer, STDIN_FILENO);
			ft_bzero((*ctx)->buffer, PIPE_BUFFER);
		}
		if (node->as.binaryExpression.right)
			exec_tree(node->as.binaryExpression.right, ctx);
	}
}

static void	exec_redirect(t_ast_node *node, t_ctx **ctx)
{
	t_ast_node	*tmp;

	if (node->as.binaryExpression.left)
		exec_tree(node->as.binaryExpression.left, ctx);
	if ((*ctx)->buffer[0])
	{
		tmp = node->as.binaryExpression.right;
		cmd_redirect(tmp->token->start, node->type, ctx);
	}
}

void	exec_tree(t_ast_node *node, t_ctx **ctx)
{
	if (node == NULL)
		return ;
	else if (node->type == NODE_COMMAND && node->token->start)
		cmd_try_run(ctx, node->token->start);
	else if (node->type == NODE_AND || node->type == NODE_OR)
		exec_and_or(node, ctx);
	else if (node->type == NODE_REDIRECT || node->type == NODE_REDIRECT_APPEND)
		exec_redirect(node, ctx);
	else if (node->type == NODE_PIPE)
		exec_pipe(node, ctx);
}
