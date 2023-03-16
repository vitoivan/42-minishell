/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:38:20 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/16 15:38:55 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_pipe(t_ast_node *node, t_ctx **ctx)
{
	if (node->u_as.s_binary_expression.left)
		exec_tree(node->u_as.s_binary_expression.left, ctx);
	if (node->u_as.s_binary_expression.right)
		exec_tree(node->u_as.s_binary_expression.right, ctx);
}

static void	exec_and_or(t_ast_node *node, t_ctx **ctx)
{
	if (node->u_as.s_binary_expression.left)
		exec_tree(node->u_as.s_binary_expression.left, ctx);
	if ((node->type == NODE_AND && (*ctx)->status_code == EXIT_SUCCESS)
		|| (node->type == NODE_OR && (*ctx)->status_code != EXIT_SUCCESS))
	{
		if ((*ctx)->buffer[0])
		{
			ft_putstr_fd((*ctx)->buffer, STDIN_FILENO);
			ft_bzero((*ctx)->buffer, PIPE_BUFFER);
		}
		if (node->u_as.s_binary_expression.right)
			exec_tree(node->u_as.s_binary_expression.right, ctx);
	}
}

static void	exec_redirect(t_ast_node *node, t_ctx **ctx)
{
	t_ast_node	*tmp;

	if (node->u_as.s_binary_expression.left)
		exec_tree(node->u_as.s_binary_expression.left, ctx);
	if ((*ctx)->buffer[0])
	{
		tmp = node->u_as.s_binary_expression.right;
		cmd_redirect(tmp->token->start, node->type, ctx);
	}
}

static void	exec_redirect_input(t_ast_node *node, t_ctx **ctx)
{
	t_ast_node	*tmp;
	char		*tmp2;

	tmp = node->u_as.s_binary_expression.right;
	if (node->type == NODE_REDIRECT_INPUT)
		cmd_redirect(tmp->token->start, node->type, ctx);
	else if (node->type == NODE_HERE_DOCUMENT)
	{
		tmp2 = ft_strjoin(tmp->token->start, "\n");
		ft_bzero((*ctx)->buffer, PIPE_BUFFER);
		ft_strlcpy((*ctx)->buffer, tmp2, PIPE_BUFFER);
		free(tmp2);
	}
	if (node->u_as.s_binary_expression.left)
		exec_tree(node->u_as.s_binary_expression.left, ctx);
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
	else if (node->type == NODE_REDIRECT_INPUT
			|| node->type == NODE_HERE_DOCUMENT)
		exec_redirect_input(node, ctx);
	else if (node->type == NODE_PIPE)
		exec_pipe(node, ctx);
}
