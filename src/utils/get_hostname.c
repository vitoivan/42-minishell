/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hostname.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:54:35 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/28 10:28:21 by vivan-de         ###   ########.fr       */
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

char	*get_hostname(char **envp)
{
	char	*path;
	char	**args;

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
	return (get_hostname_run_cmd(path, args, envp));
}
