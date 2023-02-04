/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   await_cmd_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/04 19:37:20 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

BOOL	await_cmd_run(char *binary_path, char **args, char **envp)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(binary_path, (char *const *)args, envp) == -1)
			return (False);
	}
	else
	{
		waitpid(pid, &status, 0);
		errno = WEXITSTATUS(status);
	}
	return (True);
}
