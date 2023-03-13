/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/12 19:58:07 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cd(char *path)
{
	if (chdir(path) == -1)
		return (False);
	return (True);
}

int	cmd_cd(t_ctx **ctx, char *line)
{
	char	*path;
	int		return_value;

	path = line + 3;
	return_value = cd(path);
	if (return_value == -1)
		(*ctx)->status_code = 1;
	return (return_value);
}
