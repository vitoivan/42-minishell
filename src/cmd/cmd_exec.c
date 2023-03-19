/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/19 07:22:41 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

BOOL	cmd_exec(char *line, t_ctx **ctx)
{
	char	*cmd;
	char	*binary_path;
	char	**args;

	cmd = get_cmd_from_line(line);
	binary_path = get_cmd_binary_path(cmd);
	free(cmd);
	cmd_get_args(&args, line);
	if (await_cmd_run(ctx, binary_path, args) == False)
		ft_putstr_fd("Não foi possivel rodar o comando", STDERR_FILENO);
	free(binary_path);
	cmd_free_args(&args);
	return (1);
}
