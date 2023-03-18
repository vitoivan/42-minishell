/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 10:19:03 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/18 16:58:51 by vivan-de         ###   ########.fr       */
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
	if (!g_ctx)
		return (NULL);
	return (ft_split(ctx_get_env(&g_ctx, "PATH"), ':'));
}

char	*get_cmd_binary_path(char *cmd)
{
	char	**path;
	char	*binary;
	char	*tmp;
	char	**cursor;

	path = get_path();
	if (!path)
		return (NULL);
	cursor = path;
	while (*cursor)
	{
		tmp = ft_strjoin(*cursor, "/");
		binary = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(binary, F_OK) == 0)
		{
			free_path(path);
			return (binary);
		}
		if (access(cmd, F_OK) == 0)
		{
			free_path(path);
			free(binary);
			return (ft_strdup(cmd));
		}
		cursor++;
	}
	free_path(path);
	return (NULL);
}
