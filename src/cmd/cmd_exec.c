/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/05 12:05:12 by victor.simo      ###   ########.fr       */
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
