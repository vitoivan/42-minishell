/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/05 13:09:22 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

BOOL	cmd_exec(char *line, char **envp)
{
	char	*cmd;
	char	*binary_path;
	char	**args;

	cmd = get_cmd_from_line(line);
	binary_path = get_cmd_binary_path(cmd);
	free(cmd);
	cmd_get_args(&args, line);
	await_cmd_run(binary_path, args, envp);
	free(binary_path);
	cmd_free_args(&args);
	return (1);
}
