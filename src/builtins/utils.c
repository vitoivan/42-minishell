/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 13:53:32 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/20 14:17:06 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	compare_equality(char *s1, char *s2, int len)
{
	int	str1_len;

	str1_len = ft_strlen(s1);
	if (str1_len == len)
		return (ft_strncmp(s1, s2, len) == 0);
	else if (str1_len < len)
		return (0);
	else
	{
		if (ft_isspace(s1[len]) || s1[len] == '\0' || s1[len] == '\n')
			return (ft_strncmp(s1, s2, len) == 0);
	}
	return (0);
}

BOOL	is_builtin(char *cmd)
{
	if (compare_equality(cmd, "echo", 4))
		return (True);
	if (compare_equality(cmd, "cd", 2))
		return (True);
	if (compare_equality(cmd, "pwd", 3))
		return (True);
	if (compare_equality(cmd, "export", 6))
		return (True);
	if (compare_equality(cmd, "unset", 5))
		return (True);
	if (compare_equality(cmd, "env", 3))
		return (True);
	if (compare_equality(cmd, "exit", 4))
		return (True);
	if (compare_equality(cmd, "clear", 5))
		return (True);
	return (False);
}
