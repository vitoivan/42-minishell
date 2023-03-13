/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:37:22 by jv                #+#    #+#             */
/*   Updated: 2023/03/12 20:01:08 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_cmd_not_found_err(char *cmd)
{
	char	*err_str;

	err_str = ft_strjoin(cmd, ": command not found\n");
	return (err_str);
}

static char	*get_invalid_cmd_err(t_ctx **ctx, char *line)
{
	char	*err_str;
	char	*tmp;

	tmp = ft_strjoin(line, ": ");
	err_str = ft_strjoin(tmp, strerror((*ctx)->status_code));
	free(tmp);
	tmp = ft_strjoin(err_str, "\n");
	free(err_str);
	return (tmp);
}

void	print_errno(t_ctx **ctx, char *line)
{
	char	*cmd;
	char	*err_str;

	cmd = get_cmd_from_line(line);
	err_str = NULL;
	if ((*ctx)->status_code == 127)
	{
		err_str = get_cmd_not_found_err(cmd);
		ft_putstr_fd(err_str, STDERR_FILENO);
	}
	else if (!cmd_is_valid(cmd))
	{
		err_str = get_invalid_cmd_err(ctx, line);
		ft_putstr_fd(err_str, STDERR_FILENO);
	}
	free_if_exists((void **)&err_str);
	free(cmd);
}
