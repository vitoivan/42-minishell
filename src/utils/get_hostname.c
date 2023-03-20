/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hostname.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/19 17:26:28 by vivan-de         ###   ########.fr       */
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

	(void)path;
	(void)args;
	read_buffer = ft_calloc(1, HOSTNAME_SIZE);
	buffer = ft_calloc(1, HOSTNAME_SIZE);
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
	args = NULL;
	path = NULL;
	if (get_hostname_path(&path) == False)
	{
		if (path)
			free(path);
		return (NULL);
	}
	if (get_hostname_args(&args) == False)
	{
		free_hostname_data(path, args);
		return (NULL);
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		pipe_close_both(pipefd);
		execve(path, args, envp);
		free_hostname_data(path, args);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		free_hostname_data(path, args);
		return (get_buffer_from_pipe(pipefd, path, args));
	}
	return (NULL);
}
