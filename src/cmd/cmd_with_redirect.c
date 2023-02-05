/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_with_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/05 12:23:50 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_with_redirect(char *line, char *filepath, t_ctx **ctx)
{
	int		pid;
	int		pipefd[2];
	int		fileout;
	char	*cmd;
	char	*binary_path;
	char	**args;
	int		status;

	(void)ctx;
	ft_printf("line: %s\npath: %s\n", line, filepath);
	pid = fork();
	if (pid == 0)
	{
		if (pipe(pipefd) == -1)
			ft_putstr_fd("Error creating pipe\n", STDERR_FILENO);
		pipe_close_read(pipefd);
		fileout = open(filepath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fileout == -1)
		{
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			return ;
		}
		ft_printf("here4\n");
		dup2(fileout, STDOUT_FILENO);
		cmd = get_cmd_from_line(line);
		binary_path = get_cmd_binary_path(cmd);
		if (!binary_path)
		{
			ft_putstr_fd("command not found: cmd", STDERR_FILENO);
			free(cmd);
			pipe_close_write(pipefd);
			return ;
		}
		free(cmd);
		cmd_get_args(&args, line);
		execve(binary_path, args, NULL);
	}
	else
	{
		waitpid(pid, &status, 0);
		ft_printf("status: %d\n", status);
	}
}
