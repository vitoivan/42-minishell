/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_from_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivan-de <vivan-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 09:58:10 by vivan-de          #+#    #+#             */
/*   Updated: 2023/03/16 15:30:29 by vivan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_cmd_from_line(char *line)
{
	char	*cmd;
	char	*tmp;

	if (!line)
		return (NULL);
	tmp = line;
	while (*tmp && *tmp != ' ')
		tmp++;
	cmd = ft_calloc(tmp - line + 1, sizeof(char));
	ft_strlcpy(cmd, line, tmp - line + 1);
	return (cmd);
}
