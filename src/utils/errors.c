/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor.simoes <victor.simoes@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:37:22 by jv                #+#    #+#             */
/*   Updated: 2023/02/20 15:00:21 by victor.simo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_errno(char *line)
{
	char	*cmd;

	cmd = get_cmd_from_line(line);
	if (errno == 127)
		ft_printf("%s: command not found\n", line);
	else if (!cmd_is_valid(cmd))
		ft_printf("%s: %s\n", line, strerror(errno));
	free(cmd);
}
