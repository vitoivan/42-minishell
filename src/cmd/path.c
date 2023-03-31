/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 10:19:03 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/30 21:56:30 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_path(char **path)
{
	int	i;

	if (!path)
		return ;
	i = -1;
	while (path[++i])
	{
		if (path[i])
			free(path[i]);
	}
	free(path);
}

char	**get_path(void)
{
	char	*env;
	char	**splitted;

	if (!g_ctx)
		return (NULL);
	env = ctx_get_env(&g_ctx, "PATH");
	if (!env)
		return (NULL);
	splitted = ft_split(env, ':');
	free(env);
	return (splitted);
}

static char	*get_binary(char *cmd, char *cursor)
{
	char	*binary;
	char	*tmp;

	tmp = ft_strjoin(cursor, "/");
	binary = ft_strjoin(tmp, cmd);
	free(tmp);
	if (access(binary, F_OK) == 0)
		return (binary);
	if (access(cmd, F_OK) == 0)
	{
		free(binary);
		binary = ft_strdup(cmd);
		return (binary);
	}
	free(binary);
	return (NULL);
}

char	*get_cmd_binary_path(char *cmd)
{
	char	**path;
	char	*binary;
	char	**cursor;

	path = get_path();
	cursor = path;
	while (path && *cursor)
	{
		binary = get_binary(cmd, *cursor);
		if (binary)
		{
			free_path(path);
			return (binary);
		}
		cursor++;
	}
	free_path(path);
	binary = get_binary(cmd, "");
	if (binary)
		return (binary);
	return (NULL);
}
