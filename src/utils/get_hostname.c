/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hostname.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/04 12:40:13 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static BOOL	get_hostname_path(char **path)
{
	*path = get_cmd_binary_path("hostname");
	if (!*path)
		return (False);
	return (True);
}

static BOOL	get_hostname_args(char ***args)
{
	*args = (char **)ft_calloc(3, sizeof(char *));
	if (!*args)
		return (False);
	**args = ft_strdup("hostname");
	if (!**args)
	{
		free(*args);
		return (False);
	}
	return (True);
}

static void	free_hostname_data(char *path, char **args)
{
	free_if_exists((void **)&path);
	free_if_exists((void **)&args[0]);
	free(args);
}

static char	*get_buffer_from_pipe(int pipefd[2], char *path, char **args)
{
	char	*read_buffer;
	char	*buffer;

	read_buffer = ft_calloc(1, HOSTNAME_SIZE);
	buffer = ft_calloc(1, HOSTNAME_SIZE);
	free_hostname_data(path, args);
	read(pipefd[0], read_buffer, HOSTNAME_SIZE);
	pipe_close_both(pipefd);
	ft_strlcpy(buffer, read_buffer, ft_strlen(read_buffer));
	free(read_buffer);
	return (buffer);
}

char	*get_hostname(char **envp)
{
	int		pid;
	int		pipefd[2];
	char	*path;
	char	**args;

	if (pipe(pipefd) == -1)
		return (NULL);
	if (get_hostname_path(&path) == False || get_hostname_args(&args) == False)
		return (NULL);
	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		pipe_close_both(pipefd);
		execve(path, args, envp);
	}
	else
	{
		waitpid(pid, NULL, 0);
		return (get_buffer_from_pipe(pipefd, path, args));
	}
	return (NULL);
}
