/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:37:22 by jv                #+#    #+#             */
/*   Updated: 2023/03/10 22:45:22 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_cmd_not_found_err(char *cmd)
{
	char	*err_str;

	err_str = ft_strjoin(cmd, ": command not found\n");
	return (err_str);
}

static char	*get_invalid_cmd_err(char *line)
{
	char	*err_str;
	char	*tmp;

	tmp = ft_strjoin(line, ": ");
	err_str = ft_strjoin(tmp, strerror(errno));
	free(tmp);
	tmp = ft_strjoin(err_str, "\n");
	free(err_str);
	return (tmp);
}

void	print_errno(char *line)
{
	char	*cmd;
	char	*err_str;

	cmd = get_cmd_from_line(line);
	if (errno == 127)
	{
		err_str = get_cmd_not_found_err(cmd);
		ft_putstr_fd(err_str, STDERR_FILENO);
	}
	else if (!cmd_is_valid(cmd))
	{
		err_str = get_invalid_cmd_err(line);
		ft_putstr_fd(err_str, STDERR_FILENO);
	}
	free_if_exists((void **)&err_str);
	free(cmd);
}
