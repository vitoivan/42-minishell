/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:38:20 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/19 08:53:47 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	exec_pipe(t_ast_node *node, t_ctx **ctx)
// {
// 	if (node->u_as.s_binary_expression.left)
// 		exec_tree(node->u_as.s_binary_expression.left, ctx);
// 	if (node->u_as.s_binary_expression.right)
// 		exec_tree(node->u_as.s_binary_expression.right, ctx);
// }

static void	exec_and_or(t_ast_node *node, t_ctx **ctx, int in_pipe)
{
	if (node->u_as.s_binary_expression.left)
		exec_tree(node->u_as.s_binary_expression.left, ctx, in_pipe);
	if ((node->type == NODE_AND && (*ctx)->status_code == EXIT_SUCCESS)
		|| (node->type == NODE_OR && (*ctx)->status_code != EXIT_SUCCESS))
	{
		if ((*ctx)->buffer[0])
		{
			ft_putstr_fd((*ctx)->buffer, STDIN_FILENO);
			ft_bzero((*ctx)->buffer, PIPE_BUFFER);
		}
		if (node->u_as.s_binary_expression.right)
			exec_tree(node->u_as.s_binary_expression.right, ctx, in_pipe);
	}
}

static void	exec_redirect(t_ast_node *node, t_ctx **ctx, int in_pipe)
{
	t_ast_node	*tmp;
	int			fileout;
	int			pid;

	fileout = -1;
	tmp = node->u_as.s_binary_expression.right;
	if (node->type == NODE_REDIRECT)
		fileout = open(tmp->token->start, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->type == NODE_REDIRECT_APPEND)
		fileout = open(tmp->token->start, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (node->type == NODE_REDIRECT_INPUT)
		fileout = open(tmp->token->start, O_RDONLY);
	if (fileout == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("No such file or directory: ", 2);
		ft_putstr_fd(tmp->token->start, 2);
		ft_putstr_fd("\n", 2);
		(*ctx)->status_code = 1;
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (fileout != -1)
		{
			dup2(fileout, STDOUT_FILENO);
			close(fileout);
		}
		exec_tree(node->u_as.s_binary_expression.left, ctx, in_pipe);
		ctx_free(ctx);
		exit(0);
	}
	else
	{
		if (fileout != -1)
			close(fileout);
		waitpid(pid, &(*ctx)->status_code, 0);
	}
}

static void	exec_redirect_input(t_ast_node *node, t_ctx **ctx, int in_pipe)
{
	t_ast_node	*tmp;
	pid_t		pid;
	int			filein;
	char		*tmp2;
	int			fileout;
	char		*trimmed;

	tmp = node->u_as.s_binary_expression.right;
	filein = -1;
	if (node->type == NODE_REDIRECT_INPUT)
	{
		ft_putstr_fd(tmp->token->start, 2);
		trimmed = ft_strtrim(tmp->token->start, " ");
		filein = open(trimmed, O_RDONLY);
		if (filein == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(tmp->token->start, 2);
			ft_putstr_fd(": No such file or directory: ", 2);
			ft_putstr_fd(tmp->token->start, 2);
			ft_putstr_fd("\n", 2);
			(*ctx)->status_code = 1;
			return ;
		}
	}
	else if (node->type == NODE_HERE_DOCUMENT)
	{
		fileout = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fileout == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(tmp->token->start, 2);
			ft_putstr_fd(": No such file or directory: ", 2);
			ft_putstr_fd("heredoc\n", 2);
			(*ctx)->status_code = 1;
			return ;
		}
		tmp2 = ft_strjoin(tmp->token->start, "\n");
		write(fileout, tmp2, ft_strlen(tmp2));
		free(tmp2);
		close(fileout);
		fileout = -1;
		filein = open("heredoc", O_RDONLY);
	}
	pid = fork();
	if (pid == 0)
	{
		if (filein != -1)
		{
			dup2(filein, STDIN_FILENO);
			close(filein);
		}
		if (fileout != -1)
			close(fileout);
		exec_tree(node->u_as.s_binary_expression.left, ctx, in_pipe);
		ctx_free(ctx);
		exit(0);
	}
	else
	{
		if (filein != -1)
			close(filein);
		if (fileout != -1)
			close(fileout);
		if (node->type == NODE_HERE_DOCUMENT)
			unlink("heredoc");
		(*ctx)->pid_list[(*ctx)->pid_list_i++] = pid;
	}
}

static void	close_all_pipes(void)
{
	int	j;

	j = 0;
	while (j < PIPE_LIST_SIZE)
	{
		if (g_ctx->pipe_list[j][0] != -1 && g_ctx->pipe_list[j][1] != -1)
		{
			close(g_ctx->pipe_list[j][0]);
			close(g_ctx->pipe_list[j][1]);
			g_ctx->pipe_list[j][0] = -1;
			g_ctx->pipe_list[j][1] = -1;
		}
		j++;
	}
}

static void	handle_pipes(t_ast_node *node, t_ctx **ctx, int in_pipe)
{
	int		pipefd[2];
	pid_t	pid;
	pid_t	pid2;

	if (pipe(pipefd) == -1)
		return ;
	if (in_pipe == False)
		in_pipe = True;
	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		close_all_pipes();
		exec_tree(node->u_as.s_binary_expression.left, ctx, in_pipe);
		ctx_free(ctx);
		exit(0);
	}
	else
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			close_all_pipes();
			exec_tree(node->u_as.s_binary_expression.right, ctx, in_pipe);
			ctx_free(ctx);
			exit(0);
		}
		else
		{
			// (*ctx)->pid_list[(*ctx)->pid_list_i++] = pid;
			// (*ctx)->pid_list[(*ctx)->pid_list_i++] = pid2;
			// (*ctx)->pipe_list[(*ctx)->pipe_list_i][0] = pipefd[0];
			// (*ctx)->pipe_list[(*ctx)->pipe_list_i][1] = pipefd[1];
			// (*ctx)->pipe_list_i++;
			close_all_pipes();
			waitpid(pid, &(*ctx)->status_code, 0);
			waitpid(pid2, &(*ctx)->status_code, 0);
		}
	}
}

void	exec_tree(t_ast_node *node, t_ctx **ctx, int is_in_pipe)
{
	if (node == NULL)
		return ;
	else if (node->type == NODE_COMMAND && node->token->start)
		cmd_try_run(ctx, node->token->start, is_in_pipe);
	else if (node->type == NODE_AND || node->type == NODE_OR)
		exec_and_or(node, ctx, is_in_pipe);
	else if (node->type == NODE_REDIRECT || node->type == NODE_REDIRECT_APPEND)
		exec_redirect(node, ctx, is_in_pipe);
	else if (node->type == NODE_REDIRECT_INPUT
			|| node->type == NODE_HERE_DOCUMENT)
		exec_redirect_input(node, ctx, is_in_pipe);
	else if (node->type == NODE_PIPE)
		handle_pipes(node, ctx, is_in_pipe);
}
