/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   await_cmd_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/30 03:47:03 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static BOOL	run_child(t_ctx **ctx, t_await_cmd_run_props *data,
		char *binary_path, char **args)
{
	dup2(data->parent_write_pipe[0], STDIN_FILENO);
	dup2(data->child_write_pipe[1], STDOUT_FILENO);
	pipe_close_both(data->child_write_pipe);
	pipe_close_both(data->parent_write_pipe);
	ft_printf("-");
	data->env = parse_ldk_lst_to_char_array((*ctx)->env);
	if (execve(binary_path, (char *const *)args, data->env) == -1)
		return (False);
	return (True);
}

static void	create_pipes2(t_await_cmd_run_props *data)
{
	if (!pipe_create(data->child_write_pipe)
		|| !pipe_create(data->parent_write_pipe))
	{
		ft_putstr_fd("pipe error\n", STDERR_FILENO);
		exit(1);
	}
}

static void	populate_buffer(t_ctx **ctx, t_await_cmd_run_props *data)
{
	if (data->status == 0)
	{
		ft_bzero(data->buffer, PIPE_BUFFER);
		data->read_ret = read(data->child_write_pipe[0], &(data->buffer),
				PIPE_BUFFER);
		if (data->read_ret > 1)
			ft_strlcpy((*ctx)->buffer, data->buffer + 1, PIPE_BUFFER - 1);
		ft_bzero(data->buffer, PIPE_BUFFER);
	}
	else
		ft_bzero((*ctx)->buffer, PIPE_BUFFER);
}

BOOL	await_cmd_run(t_ctx **ctx, char *binary_path, char **args)
{
	t_await_cmd_run_props	data;

	create_pipes2(&data);
	(*ctx)->pid = fork();
	if ((*ctx)->pid == 0 && run_child(ctx, &data, binary_path, args) == False)
		return (False);
	else
	{
		if ((*ctx)->buffer[0])
		{
			ft_putstr_fd((*ctx)->buffer, data.parent_write_pipe[1]);
			ft_bzero((*ctx)->buffer, PIPE_BUFFER);
		}
		pipe_close_both(data.parent_write_pipe);
		waitpid((*ctx)->pid, &(data.status), 0);
		populate_buffer(ctx, &data);
		pipe_close_both(data.child_write_pipe);
		(*ctx)->status_code = WEXITSTATUS(data.status);
		(*ctx)->pid = -1;
	}
	return (True);
}
