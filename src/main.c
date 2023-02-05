/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/05 15:28:29 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_tree(AstNode *node, t_ctx **ctx)
{
	if (node == NULL)
		return ;
	if (node->type == NODE_COMMAND)
		cmd_try_run(ctx, node->token->start);
	if (node->type == NODE_AND || node->type == NODE_OR)
	{
		if (node->as.binaryExpression.left)
			exec_tree(node->as.binaryExpression.left, ctx);
		if (node->type == NODE_OR || errno == EXIT_SUCCESS)
		{
			if (node->as.binaryExpression.right)
				exec_tree(node->as.binaryExpression.right, ctx);
		}
	}
	if (node->type == NODE_REDIRECT || node->type == NODE_REDIRECT_APPEND)
	{
		// run first command with redirection to the second one
		cmd_with_redirect(node->as.binaryExpression.left->token->start,
							node->as.binaryExpression.right->token->start,
							node->type,
							ctx);
	}
	if (node->type == NODE_PIPE)
	{
		// run both commands here
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_ctx	*ctx;

	line = NULL;
	ctx = ctx_init(argc, argv, envp);
	while (True)
	{
		if (!get_line_from_terminal(&line, ctx) || !line)
			return (1);
		if (line[0] == '\0' || line[0] == '\n')
			continue ;
		ctx->root_cmd = ft_parser(line);
		if (line)
			free(line);
		if (ctx->root_cmd)
		{
			exec_tree(ctx->root_cmd, &ctx);
			ast_node_free(ctx->root_cmd);
		}
	}
	return (0);
}
