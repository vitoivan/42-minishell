/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/31 10:09:34 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_cd_path(char *line)
{
	char	*path;

	path = line + 2;
	while (*path == ' ')
		path++;
	if (*path == '\0')
		path = ctx_get_env(&g_ctx, "HOME");
	return (path);
}

int	cmd_cd(t_ctx **ctx, char *line)
{
	char	*path;

	path = get_cd_path(line);
	if (path == NULL)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		(*ctx)->status_code = 1;
		return (1);
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(path, 2);
		(*ctx)->status_code = 1;
		return (1);
	}
	return (0);
}
