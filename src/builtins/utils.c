/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2022/12/26 07:03:59 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

BOOL	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4))
		return (True);
	if (!ft_strncmp(cmd, "cd", 2))
		return (True);
	if (!ft_strncmp(cmd, "pwd", 3))
		return (True);
	if (!ft_strncmp(cmd, "export", 6))
		return (True);
	if (!ft_strncmp(cmd, "unset", 5))
		return (True);
	if (!ft_strncmp(cmd, "env", 3))
		return (True);
	if (!ft_strncmp(cmd, "exit", 4))
		return (True);
	return (False);
}
