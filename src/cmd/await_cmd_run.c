/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   await_cmd_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/12 20:19:05 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

BOOL	await_cmd_run(t_ctx **ctx, char *binary_path, char **args)
{
	int		status;
	int		parent_write_pipe[2];
	int		child_write_pipe[2];
	int		read_ret;
	char	buffer[PIPE_BUFFER];
	char	**env;

	if (!pipe_create(child_write_pipe) || !pipe_create(parent_write_pipe))
	{
		ft_putstr_fd("pipe error\n", STDERR_FILENO);
		exit(1);
	}
	(*ctx)->pid = fork();
	if ((*ctx)->pid == 0)
	{
		dup2(parent_write_pipe[0], STDIN_FILENO);
		dup2(child_write_pipe[1], STDOUT_FILENO);
		pipe_close_both(child_write_pipe);
		pipe_close_both(parent_write_pipe);
		ft_printf("-");
		env = parse_ldk_lst_to_char_array((*ctx)->env);
		if (execve(binary_path, (char *const *)args, env) == -1)
			return (False);
	}
	else
	{
		if ((*ctx)->buffer[0])
		{
			ft_putstr_fd((*ctx)->buffer, parent_write_pipe[1]);
			ft_bzero((*ctx)->buffer, PIPE_BUFFER);
		}
		pipe_close_both(parent_write_pipe);
		waitpid((*ctx)->pid, &status, 0);
		if (status == 0)
		{
			ft_bzero(buffer, PIPE_BUFFER);
			read_ret = read(child_write_pipe[0], &buffer, PIPE_BUFFER);
			if (read_ret > 1)
				ft_strlcpy((*ctx)->buffer, buffer + 1, PIPE_BUFFER - 1);
			ft_bzero(buffer, PIPE_BUFFER);
		}
		else
			ft_bzero((*ctx)->buffer, PIPE_BUFFER);
		pipe_close_both(child_write_pipe);
		(*ctx)->status_code = WEXITSTATUS(status);
		(*ctx)->pid = -1;
	}
	return (True);
}
