/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   await_cmd_run.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/19 03:16:25 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

BOOL	await_cmd_run(t_ctx **ctx, char *binary_path, char **args)
{
	char	**env;

	env = parse_ldk_lst_to_char_array((*ctx)->env);
	if (execve(binary_path, (char *const *)args, env) == -1)
		return (False);
	return (True);
}
