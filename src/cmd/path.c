/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 10:19:03 by vivan-de          #+#    #+#             */
/*   Updated: 2022/12/11 14:49:54 by vivan-de         ###   ########.fr       */
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
	return (ft_split(getenv("PATH"), ':'));
}

char	*get_cmd_binary_path(char *cmd)
{
	char	**path;
	char	*binary;
	char	*tmp;
	char	**cursor;

	path = get_path();
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
		free(binary);
		cursor++;
	}
	free_path(path);
	return (NULL);
}
