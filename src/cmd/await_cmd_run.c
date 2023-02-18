/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   await_cmd_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/18 18:20:03 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

BOOL	await_cmd_run(char *binary_path, char **args, t_ctx **ctx)
{
	int		pid;
	int		status;
	int		parent_write_pipe[2];
	int		child_write_pipe[2];
	int		read_ret;
	char	buffer[PIPE_BUFFER];

	if (!pipe_create(child_write_pipe) || !pipe_create(parent_write_pipe))
	{
		ft_printf("pipe error\n");
		exit(1);
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(parent_write_pipe[0], STDIN_FILENO);
		dup2(child_write_pipe[1], STDOUT_FILENO);
		pipe_close_both(child_write_pipe);
		pipe_close_both(parent_write_pipe);
		ft_printf("-");
		if (execve(binary_path, (char *const *)args, (*ctx)->env) == -1)
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
		waitpid(pid, &status, 0);
		if (status == 0)
		{
			read_ret = read(child_write_pipe[0], &buffer, PIPE_BUFFER);
			if (read_ret > 1)
				ft_strlcpy((*ctx)->buffer, buffer + 1, PIPE_BUFFER - 1);
			ft_bzero(buffer, PIPE_BUFFER);
		}
		else
			ft_bzero((*ctx)->buffer, PIPE_BUFFER);
		pipe_close_both(child_write_pipe);
		errno = WEXITSTATUS(status);
	}
	return (True);
}
