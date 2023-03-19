/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:37:22 by jv                #+#    #+#             */
/*   Updated: 2023/03/19 08:46:29 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_cmd_not_found_err(char *cmd)
{
	char	*err_str;

	err_str = ft_strjoin(cmd, ": command not found\n");
	return (err_str);
}
void	print_errno(t_ctx **ctx, char *line, int status_code)
{
	char	*cmd;
	char	*err_str;

	cmd = get_cmd_from_line(line);
	err_str = NULL;
	(void)ctx;
	if (status_code == 127)
	{
		err_str = get_cmd_not_found_err(cmd);
		ft_putstr_fd(err_str, 2);
	}
	else if (!cmd_is_valid(cmd))
	{
		ft_putstr_fd(line, 2);
		ft_putstr_fd(" : ", 2);
		ft_putstr_fd(strerror(status_code), 2);
		ft_putstr_fd("\n", 2);
	}
	free_if_exists((void **)&err_str);
	free(cmd);
}
