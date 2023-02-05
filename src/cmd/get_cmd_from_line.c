/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_from_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/02/05 12:03:56 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_cmd_from_line(char *line)
{
	char *cmd;
	char *tmp;

	tmp = line;
	while (*tmp && *tmp != ' ')
		tmp++;
	cmd = ft_calloc(tmp - line + 1, sizeof(char));
	ft_strlcpy(cmd, line, tmp - line + 1);
	return (cmd);
}